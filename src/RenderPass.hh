#ifndef RENDERPASS_H
#define RENDERPASS_H

#include <QVector>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>

class RenderPass
{
public:
    RenderPass();
    ~RenderPass();

    QOpenGLShaderProgram *getProgram() const { return (_program); }

    void setVertexCode(QString code);
    void setFragmentCode(QString code);

private:
    QString _vertexCode;
    QString _fragmentCode;

    GLuint _fbo;
    QOpenGLShader *_vertex;
    QOpenGLShader *_fragment;
    QOpenGLShaderProgram *_program;

    RenderPass *_previous;
    QVector<RenderPass *> _next;
};

#endif // RENDERPASS_H
