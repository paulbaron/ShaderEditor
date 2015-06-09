#ifndef DATASTRUCTUREEDITOR_HH
#define DATASTRUCTUREEDITOR_HH

#include <QWidget>
#include <QStringList>

namespace Ui {
class DataStructureEditor;
}

class DataStructureEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DataStructureEditor(QWidget *parent = 0);
    ~DataStructureEditor();

public slots:
    void createData();
    void deleteData();
    void selectionChanged();

private:
    Ui::DataStructureEditor *ui;

    QStringList _dataTypes;
};

#endif // DATASTRUCTUREEDITOR_HH
