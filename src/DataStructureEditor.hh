#ifndef DATASTRUCTUREEDITOR_HH
#define DATASTRUCTUREEDITOR_HH

#include <QWidget>
#include <QStringList>
#include <QModelIndex>

#include <QTreeWidgetItem>

#include <QDataStream>

#include "RenderPassUi.h"

class ContainerView;

namespace Ui {
class DataStructureEditor;
}

class DataStructureEditor : public QWidget
{
    Q_OBJECT

public:
    explicit DataStructureEditor(RenderPassUi *renderPassui, QWidget *parent = 0);
    ~DataStructureEditor();

    void reloadUi();

public slots:
    void createData();
    void deleteData();
    void selectionChanged();

    void setAddSon();
    void setRemoveSon();

signals:
    void sonAdded(bool checked);
    void sonRemoved(bool checked);

private:
    void recursiveDeleteDataFromRenderPass(SInstance *data);

    Ui::DataStructureEditor *ui;
    ContainerView *_containerView;

    QStringList _dataTypes;
    QTreeWidgetItem *_currentSelection;
    bool _addSon;
    bool _removeSon;

    bool _isAddingSon;
    bool _isRemovingSon;

    RenderPassUi *_renderPassUi;
};

#endif // DATASTRUCTUREEDITOR_HH
