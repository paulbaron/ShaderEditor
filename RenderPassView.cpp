#include "RenderPassView.hh"

RenderPassView::RenderPassView(QWidget *parent) :
    QGLWidget(parent)
{
//    setSizePolicy(QSizePolicy::Expanding);
    setMinimumHeight(300);
}

void RenderPassView::initializeGL()
{
    _texture = new QOpenGLTexture(QImage(QString("test.png")));
}

void RenderPassView::paintGL()
{
    glClearColor(1, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT);
}
