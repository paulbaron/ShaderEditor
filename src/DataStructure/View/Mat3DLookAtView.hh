#ifndef MAT3DLOOKAT_HH
#define MAT3DLOOKAT_HH

#include <QWidget>

namespace Ui {
class Mat3DLookAtView;
}

class Mat3DLookAtView : public QWidget
{
    Q_OBJECT

public:
    explicit Mat3DLookAtView(QWidget *parent = 0);
    ~Mat3DLookAtView();

    Ui::Mat3DLookAtView *getUi() const;

private:
    Ui::Mat3DLookAtView *ui;
};

#endif // MAT3DLOOKAT_HH
