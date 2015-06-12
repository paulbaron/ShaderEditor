#ifndef MAT3DTRANSFORMVIEW_HH
#define MAT3DTRANSFORMVIEW_HH

#include <QWidget>

namespace Ui {
class Mat3DTransformView;
}

class Mat3DTransformView : public QWidget
{
    Q_OBJECT

public:
    explicit Mat3DTransformView(QWidget *parent = 0);
    ~Mat3DTransformView();

    Ui::Mat3DTransformView *getUi() const;

private:
    Ui::Mat3DTransformView *ui;
};

#endif // MAT3DTRANSFORMVIEW_HH
