#include "RenderPassView.hh"

#include <assert.h>

RenderPassView::RenderPassView(QWidget *parent) :
    QOpenGLWidget(parent)
{
//    setSizePolicy(QSizePolicy::Expanding);
    setMinimumHeight(300);
}

void RenderPassView::initializeGL()
{
    // Initialize basic flat render shader:
    QOpenGLShader *vertex = new QOpenGLShader(QOpenGLShader::Vertex);
    QOpenGLShader *fragment = new QOpenGLShader(QOpenGLShader::Fragment);

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

    vertex->compileSourceCode(flatVertex);
    fragment->compileSourceCode(flatFragment);

    bool hasCompiled = vertex->isCompiled() && fragment->isCompiled();

    assert(hasCompiled);

    _program = new QOpenGLShaderProgram;

    _program->addShader(vertex);
    _program->addShader(fragment);
    _program->bindAttributeLocation("position", 0);
    _program->link();
    _program->bind();
    _program->setUniformValue("texture", 0);

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

void RenderPassView::paintGL()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);

    _program->bind();
    _vbo.bind();
    _program->enableAttributeArray(0);
    _program->setAttributeBuffer(0, GL_FLOAT, 0, 2);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}
