#ifndef CONTAINERVIEW_HH
#define CONTAINERVIEW_HH

#include <QWidget>
#include "../ContainerData.hh"

namespace Ui {
class ContainerView;
}

class ContainerView : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerView(bool &addSon, bool &removeSon, QWidget *parent = 0);
    ~ContainerView();

    Ui::ContainerView *getUi() const { return (ui); }

public slots:
    void setAddSon();
    void setRemoveSon();

private:
    Ui::ContainerView *ui;
    bool &_addSon;
    bool &_removeSon;
};

#endif // CONTAINERVIEW_HH
