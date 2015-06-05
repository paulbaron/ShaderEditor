#ifndef RENDERPASSVIEW_H
#define RENDERPASSVIEW_H

#include <QGLWidget>
#include <QOpenGLTexture>

class RenderPassView : public QGLWidget
{
    Q_OBJECT

public:
    RenderPassView(QWidget *parent = 0);

    void initializeGL();
    void paintGL();

private:
    QOpenGLTexture *_texture;
};

#endif // RENDERPASSVIEW_H
