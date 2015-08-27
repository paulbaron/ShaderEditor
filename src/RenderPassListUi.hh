#ifndef RENDERPASSLISTUI_HH
#define RENDERPASSLISTUI_HH

#include <QWidget>

#include "RenderPassUi.h"

namespace Ui {
class RenderPassListUi;
}

class RenderPassListUi : public QWidget
{
    Q_OBJECT

public:
    explicit RenderPassListUi(RenderPassUi *renderPassUi, QWidget *parent = 0);
    ~RenderPassListUi();

    void reloadUi();

public slots:
    void addRenderPass();
    void RenderPassSelected();

private:
    Ui::RenderPassListUi *ui;
    RenderPassUi *_renderPassUi;
};

#endif // RENDERPASSLISTUI_HH
