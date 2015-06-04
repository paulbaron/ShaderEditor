#ifndef RENDERPASSUI_H
#define RENDERPASSUI_H

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

private:
    Ui::RenderPassUi *ui;
};

#endif // RENDERPASSUI_H
