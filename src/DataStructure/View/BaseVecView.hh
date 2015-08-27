#ifndef BASEVECVIEW_HH
#define BASEVECVIEW_HH

#include <QWidget>

#include "../AbstractData.hh"

namespace Ui {
class BaseVecView;
}

class BaseVecView : public QWidget
{
    Q_OBJECT

public:
    explicit BaseVecView(AbstractData *data, QWidget *parent = 0);
    ~BaseVecView();

    Ui::BaseVecView *getUi() const { return (ui); }

protected:
    Ui::BaseVecView *ui;
};

#endif // BASEVECVIEW_HH
