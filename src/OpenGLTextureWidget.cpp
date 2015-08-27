#include "OpenGLTextureWidget.hh"
#include "RenderPassManager.hh"
#include "RenderPass.hh"

#include "QtOpenGLFunctions.hh"

#include <assert.h>

OpenGLTextureWidget::OpenGLTextureWidget(bool renderAllPass, QWidget *parent) :
    QOpenGLWidget(parent)
{
    _renderAllPass = renderAllPass;
    _shader = NULL;
    _toDraw = 0;
}

void OpenGLTextureWidget::initializeGL()
{
    if (_shader == NULL)
        _shader = new GLSLShader;
    const char *flatVertex = "attribute vec2 position;\n"
                             "\n"
                             "varying vec2 texCoord;\n"
                             "\n"
                             "void main()\n"
                             "{\n"
                             "  texCoord = position * vec2(0.5f) + vec2(0.5f);\n"
                             "  gl_Position = vec4(position, 0, 1);\n"
                             "}\n";

    const char *flatFragment = "uniform sampler2D texture;\n"
                               "\n"
                               "varying vec2 texCoord;\n"
                               "\n"
                               "void main()\n"
                               "{\n"
                               "  gl_FragColor = texture2D(texture, texCoord);\n"
                               "}\n";


    _shader->load(flatVertex, GLSLShader::VERTEX_SHADER);
    _shader->load(flatFragment, GLSLShader::FRAGMENT_SHADER);
    _shader->build();
    _shader->bind();
    _shader->bindAttribLocation(0, "position");
    _shader->bindTextureUnit(0, "texture");

    static float quadPositions[6][2] =
    {
        {-1, -1},
        {1, -1},
        {-1, 1},
        {1, -1},
        {1, 1},
        {-1, 1}
    };
    _vbo.create();
    _vbo.bind();
    _vbo.allocate(quadPositions, 6 * 2 * sizeof(float));
}

void OpenGLTextureWidget::resizeGL(int w, int h)
{
    GLContext::get()->glViewport(0, 0, w, h);
}

void OpenGLTextureWidget::paintGL()
{
    _shader->bind();

    GLContext::get()->glActiveTexture(GL_TEXTURE0);
    GLContext::get()->glBindTexture(GL_TEXTURE_2D, (GLuint)_toDraw);
    _vbo.bind();
    GLContext::get()->glEnableVertexAttribArray(0);
    GLContext::get()->glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    GLContext::get()->glDrawArrays(GL_TRIANGLES, 0, 6);
}

void OpenGLTextureWidget::textureToDisplayChanged(GLuint toDraw)
{
    _toDraw = toDraw;
}
