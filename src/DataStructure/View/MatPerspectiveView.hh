#ifndef MATPERSPECTIVEVIEW_HH
#define MATPERSPECTIVEVIEW_HH

#include <QWidget>

#include <../vendors/glm/glm.hpp>

namespace Ui {
class MatPerspectiveView;
}

class MatPerspectiveView : public QWidget
{
    Q_OBJECT

public:
    explicit MatPerspectiveView(QWidget *parent = 0);
    ~MatPerspectiveView();

    glm::mat4 getPerspective() const;
    Ui::MatPerspectiveView *getUi() const { return (ui); }

private:
    Ui::MatPerspectiveView *ui;
};

#endif // MATPERSPECTIVEVIEW_HH
