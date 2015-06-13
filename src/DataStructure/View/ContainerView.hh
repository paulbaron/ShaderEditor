#ifndef CONTAINERVIEW_HH
#define CONTAINERVIEW_HH

#include <QWidget>
#include "../ContainerData.hh"

namespace Ui {
class ContainerView;
}

class DataStructureEditor;

class ContainerView : public QWidget
{
    Q_OBJECT

public:
    explicit ContainerView(DataStructureEditor *editor, QWidget *parent = 0);
    ~ContainerView();

    Ui::ContainerView *getUi() const { return (ui); }

private:
    Ui::ContainerView *ui;
};

#endif // CONTAINERVIEW_HH
