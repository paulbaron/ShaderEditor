#include "OpenGLTextureManager.hh"
#include <assert.h>

OpenGLTextureManager *OpenGLTextureManager::_singleton = NULL;

GLenum OpenGLTextureManager::_textureFormatTable[][3] =
{
    {GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE},
    {GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE},
    {GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT},
    {GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT},
    {GL_R8, GL_RED, GL_UNSIGNED_BYTE},
    {GL_R16UI, GL_RED, GL_UNSIGNED_INT},
    {GL_R16F, GL_RED, GL_FLOAT},
    {GL_R32F, GL_RED, GL_FLOAT},
    {GL_RG8, GL_RG, GL_UNSIGNED_BYTE},
    {GL_RG16UI, GL_RG, GL_UNSIGNED_INT},
    {GL_RG16F, GL_RG, GL_FLOAT},
    {GL_RG32F, GL_RG, GL_FLOAT},
    {GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE},
    {GL_RGB16UI, GL_RGB, GL_UNSIGNED_INT},
    {GL_RGB16F, GL_RGB, GL_FLOAT},
    {GL_RGB32F, GL_RGB, GL_FLOAT},
    {GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE},
    {GL_RGBA16UI, GL_RGB, GL_UNSIGNED_INT},
    {GL_RGBA16F, GL_RGB, GL_FLOAT},
    {GL_RGBA32F, GL_RGB, GL_FLOAT},
    {(GLenum)-1, (GLenum)-1, (GLenum)-1}
};

OpenGLTextureManager::STextureData::STextureData()
{
    this->name = "~~ NO NAME ~~";
    this->id = 0;
    this->format = GL_RGBA8;
    this->width = 1280;
    this->height = 720;
    this->horizontalWrapMode = GL_CLAMP;
    this->verticalWrapMode = GL_CLAMP;
    this->magFilter = GL_LINEAR;
    this->minFilter = GL_LINEAR;
}

OpenGLTextureManager::OpenGLTextureManager()
{
}

OpenGLTextureManager *OpenGLTextureManager::getManager()
{
    if (_singleton == NULL)
        _singleton = new OpenGLTextureManager();
    return (_singleton);
}

void OpenGLTextureManager::removeTexture(QString name)
{
    for (int i = 0; i < _textures.size(); ++i)
    {
        if (_textures[i].name == name)
        {
            _textures.removeAt(i);
            return;
        }
    }
}

OpenGLTextureManager::STextureData const *OpenGLTextureManager::getTextureData(QString name) const
{
    for (int i = 0; i < _textures.size(); ++i)
    {
        if (_textures[i].name == name)
        {
            return (&_textures[i]);
        }
    }
    return (NULL);
}

void OpenGLTextureManager::removeTexture(GLuint id)
{
    for (int i = 0; i < _textures.size(); ++i)
    {
        if (_textures[i].id == id)
        {
            _textures.removeAt(i);
            return;
        }
    }
}

OpenGLTextureManager::STextureData const *OpenGLTextureManager::getTextureData(GLuint id) const
{
    for (int i = 0; i < _textures.size(); ++i)
    {
        if (_textures[i].id == id)
        {
            return (&_textures[i]);
        }
    }
    return (NULL);
}

void OpenGLTextureManager::setTextureData(STextureData const &data)
{
    GLenum format, type;
    GLuint id = data.id;

    if (id == 0)
    {
        // The texture does not exist yet
        glGenTextures(1, &id);
        _textures.push_back(data);
        _textures.back().id = id;
    }
    else
    {
        // The texture exist, just update its data
        bool textureDataFound = false;

        for (int i = 0; i < _textures.size() && !textureDataFound; ++i)
        {
            if (_textures[i].id == id)
            {
                _textures[i] = data;
                textureDataFound = true;
            }
        }
        assert(textureDataFound == true);
    }
    // Update OpenGL parameters
    getFormatInfo(data.format, format, type);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, data.format, data.width, data.height, 0, format, type, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, data.minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, data.magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, data.horizontalWrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, data.verticalWrapMode);
}

GLenum OpenGLTextureManager::getFormatFromIndex(int index) const
{
    return (_textureFormatTable[index][0]);
}

int OpenGLTextureManager::getIndexFromFormat(GLenum format) const
{
    int idx = 0;

    while (_textureFormatTable[idx][0] != (GLenum)-1 &&
           _textureFormatTable[idx][0] != format)
    {
        ++idx;
    }
    assert(_textureFormatTable[idx][0] != (GLenum)-1);
    return (idx);
}

void OpenGLTextureManager::getFormatInfo(GLenum internalFormat, GLenum &format, GLenum &type)
{
    int idx = getIndexFromFormat(internalFormat);
    format = _textureFormatTable[idx][1];
    type = _textureFormatTable[idx][2];
}
