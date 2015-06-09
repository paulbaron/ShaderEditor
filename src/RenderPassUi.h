#ifndef RENDERPASSUI_H
#define RENDERPASSUI_H

#include "RenderPass.hh"

#include <QWidget>

namespace Ui {
class RenderPassUi;
}

class RenderPassUi : public QWidget
{
    Q_OBJECT

public:
    explicit RenderPassUi(QWidget *parent = 0);
    ~RenderPassUi();

public slots:
    // When the text is modified, change the value of the shader
    void setCurrentVertexShader();
    void setCurrentFragmentShader();

private:
    Ui::RenderPassUi *ui;
    RenderPass *_currentPass;
};

#endif // RENDERPASSUI_H
