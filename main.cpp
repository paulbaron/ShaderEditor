#include <QApplication>
#include "EditorMainWindow.hpp"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    EditorMainWindow w;
    w.show();

    return a.exec();
}
