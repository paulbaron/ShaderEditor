#ifndef MATPERSPECTIVEVIEW_HH
#define MATPERSPECTIVEVIEW_HH

#include <QWidget>

namespace Ui {
class MatPerspectiveView;
}

class MatPerspectiveView : public QWidget
{
    Q_OBJECT

public:
    explicit MatPerspectiveView(QWidget *parent = 0);
    ~MatPerspectiveView();

    Ui::MatPerspectiveView *getUi() const;

private:
    Ui::MatPerspectiveView *ui;
};

#endif // MATPERSPECTIVEVIEW_HH
