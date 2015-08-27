#ifndef QIWIMAINWINDOW_HPP
#define QIWIMAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsScene>

#include "Commons.hpp"

namespace Ui
{
    class EditorMainWindow;
}

class RenderPassUi;
class RenderPassListUi;
class DataStructureEditor;

class EditorMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit EditorMainWindow(QWidget *parent = 0);
    ~EditorMainWindow();

public slots:
    void saveProject();
    void saveProjectAs();
    void loadProject();
    void newProject();

private:
    Ui::EditorMainWindow *ui;

    RenderPassUi *_renderPassUi;
    RenderPassListUi *_renderPassListUi;
    DataStructureEditor *_dataStructureEditor;
    QString _savePath;
};

#endif // QIWIMAINWINDOW_HPP
