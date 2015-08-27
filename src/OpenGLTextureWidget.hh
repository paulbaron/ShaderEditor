#ifndef RENDERPASSVIEW_H
#define RENDERPASSVIEW_H

#include "DataStructure/ATextureData.hh"

#include "GlslShader.hh"

#include <QOpenGLWidget>
#include <QOpenGLBuffer>
#include <QOpenGLFunctions>

class OpenGLTextureWidget : public QOpenGLWidget
{
    Q_OBJECT

public:
    OpenGLTextureWidget(bool renderAllPass, QWidget *parent = 0);

    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

public slots:
    void textureToDisplayChanged(GLuint toDraw);

private:
    GLSLShader *_shader;
    QOpenGLBuffer _vbo;
    GLuint _toDraw;
    bool _renderAllPass;
};

#endif // RENDERPASSVIEW_H
