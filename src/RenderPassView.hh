#ifndef RENDERPASSVIEW_H
#define RENDERPASSVIEW_H

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

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
};

#endif // RENDERPASSVIEW_H
