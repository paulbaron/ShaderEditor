#ifndef MAT4DATAVIEW_HH
#define MAT4DATAVIEW_HH

#include <QWidget>

#include "../AbstractData.hh"

namespace Ui {
class Mat4DataView;
}

class Mat4DataView : public QWidget
{
    Q_OBJECT

public:
    enum EMatrixType
    {
        Transform,
        LookAt,
        Perspective
    };

    explicit Mat4DataView(AbstractData *data, QWidget *parent = 0);
    ~Mat4DataView();

    void setPerspective();
    void setTransform();
    void setLookAt();

    Ui::Mat4DataView *getUi() const { return (ui); }
    EMatrixType getMatrixType() const { return (_type); }
    QWidget *getCurrent() const { return (_current); }

public slots:
    void matrixTypeChanged();

private:
    EMatrixType _type;
    QWidget *_current;
    Ui::Mat4DataView *ui;
};

#endif // MAT4DATAVIEW_HH
