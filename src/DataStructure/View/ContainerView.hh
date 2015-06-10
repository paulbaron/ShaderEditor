#ifndef CONTAINERVIEW_HH
#define CONTAINERVIEW_HH

#include <QWidget>

namespace Ui {
class ContainerView;
}

class ContainerView : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerView(QWidget *parent = 0);
    ~ContainerView();

private:
    Ui::ContainerView *ui;
};

#endif // CONTAINERVIEW_HH
