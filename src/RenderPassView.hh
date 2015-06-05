#ifndef RENDERPASSVIEW_H
#define RENDERPASSVIEW_H

#include "RenderPass.hh"

#include <QOpenGLWidget>
#include <QOpenGLBuffer>

class RenderPassView : public QOpenGLWidget
{
    Q_OBJECT

public:
    RenderPassView(QWidget *parent = 0);

    void initializeGL();
    void paintGL();

private:
    QOpenGLShaderProgram *_program;
    QOpenGLBuffer _vbo;
    RenderPass *_currentPass;
};

#endif // RENDERPASSVIEW_H
