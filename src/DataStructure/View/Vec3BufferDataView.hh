#ifndef VEC3BUFFERDATAVIEW_HH
#define VEC3BUFFERDATAVIEW_HH

#include <QWidget>
#include <../vendors/glm/glm.hpp>

#include "../AbstractData.hh"

namespace Ui {
class Vec3BufferDataView;
}

class Vec3BufferDataView : public QWidget
{
    Q_OBJECT

public:
    explicit Vec3BufferDataView(AbstractData *data, QWidget *parent = 0);
    ~Vec3BufferDataView();

    glm::vec3 *getData() const;
    int getDataCount() const;

public slots:
    void selectionChanged();
    void addRow();
    void deleteRow();
    void loadPreset();

private:
    Ui::Vec3BufferDataView *ui;
};

#endif // VEC3BUFFERDATAVIEW_HH
