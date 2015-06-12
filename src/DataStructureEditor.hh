#ifndef DATASTRUCTUREEDITOR_HH
#define DATASTRUCTUREEDITOR_HH

#include <QWidget>
#include <QStringList>
#include <QModelIndex>

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
    QModelIndex _currentSelection;
    bool _addSon;
    bool _removeSon;
};

#endif // DATASTRUCTUREEDITOR_HH
