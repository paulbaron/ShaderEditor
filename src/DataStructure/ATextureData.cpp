#include "ATextureData.hh"
#include "RenderPassManager.hh"
#include "RenderPass.hh"

#include "QtOpenGLFunctions.hh"

#include <assert.h>

BOOST_CLASS_EXPORT_IMPLEMENT(ATextureData)

ATextureData::ATextureData(QString prefix) :
    AbstractData(prefix)
{
    // Set the default texture parameters
    GLContext::get()->glGenTextures(1, &_id);
    _format = GL_RGBA8;
    _width = 0;
    _height = 0;
    _magFilter = GL_LINEAR;
    _minFilter = GL_LINEAR;
    _verticalWrapMode = GL_CLAMP;
    _horizontalWrapMode = GL_CLAMP;
}

ATextureData::~ATextureData()
{
    GLContext::get()->glDeleteTextures(1, &_id);
}

GLenum ATextureData::getInternalFormat() const
{
    return (_format);
}

GLuint ATextureData::getTextureId() const
{
    return (_id);
}

GLuint ATextureData::getWidth() const
{
    return (_width);
}

GLuint ATextureData::getHeight() const
{
    return (_height);
}

QString ATextureData::getInputType() const
{
    return ("uniform sampler2D");
}

void ATextureData::setInput(QString inputName, GLSLShader &program, int textureBinding)
{
    program.bindTextureUnit(textureBinding, inputName);
    GLContext::get()->glActiveTexture(GL_TEXTURE0 + textureBinding);
    GLContext::get()->glBindTexture(GL_TEXTURE_2D, _id);
}

GLenum ATextureData::getWrapModeFromIndex(int idx) const
{
    if (idx == 0)
        return (GL_REPEAT);
    else if (idx == 1)
        return (GL_MIRRORED_REPEAT);
    else if (idx == 2)
        return (GL_CLAMP);
    else
    {
        assert(!"Unknown filter index");
        return ((GLenum)-1);
    }
}

int ATextureData::getIndexFromWrapMode(GLenum wrap) const
{
    if (wrap == GL_REPEAT)
        return (0);
    else if (wrap == GL_MIRRORED_REPEAT)
        return (1);
    else if (wrap == GL_CLAMP)
        return (2);
    else
    {
        assert(!"Unknown filter");
        return (-1);
    }
}

GLenum ATextureData::getFilterModeFromIndex(int idx) const
{
    if (idx == 0)
        return (GL_LINEAR);
    else if (idx == 1)
        return (GL_NEAREST);
    else
    {
        assert(!"Unknown wrap mode index");
        return ((GLenum)-1);
    }
}

int ATextureData::getIndexFromFilterMode(GLenum filter) const
{
    if (filter == GL_LINEAR)
        return (0);
    else if (filter == GL_NEAREST)
        return (1);
    else
    {
        assert(!"Unknown filter mode");
        return (-1);
    }
}
