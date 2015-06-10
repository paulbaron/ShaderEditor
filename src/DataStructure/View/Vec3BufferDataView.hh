#ifndef VEC3BUFFERDATAVIEW_HH
#define VEC3BUFFERDATAVIEW_HH

#include <QWidget>

namespace Ui {
class Vec3BufferDataView;
}

class Vec3BufferDataView : public QWidget
{
    Q_OBJECT

public:
    explicit Vec3BufferDataView(QWidget *parent = 0);
    ~Vec3BufferDataView();

public slots:
    void selectionChanged();
    void addRow();
    void deleteRow();
    void loadPreset();
    void valueChanged();

private:
    Ui::Vec3BufferDataView *ui;
};

#endif // VEC3BUFFERDATAVIEW_HH
