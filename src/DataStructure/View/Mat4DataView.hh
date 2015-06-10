#ifndef MAT4DATAVIEW_HH
#define MAT4DATAVIEW_HH

#include <QWidget>

namespace Ui {
class Mat4DataView;
}

class Mat4DataView : public QWidget
{
    Q_OBJECT

public:
    explicit Mat4DataView(QWidget *parent = 0);
    ~Mat4DataView();

private:
    Ui::Mat4DataView *ui;
};

#endif // MAT4DATAVIEW_HH
