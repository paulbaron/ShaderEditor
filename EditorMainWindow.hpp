#ifndef QIWIMAINWINDOW_HPP
#define QIWIMAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>

#include "Commons.hpp"

namespace Ui
{
    class EditorMainWindow;
}

class EditorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorMainWindow(QWidget *parent = 0);
    ~EditorMainWindow();

private:
    Ui::EditorMainWindow *ui;
    QGraphicsScene _scene;
};

#endif // QIWIMAINWINDOW_HPP
