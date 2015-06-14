#include "DataStructureEditor.hh"
#include "ui_DataStructureEditor.h"

#include "DataStructure/View/ContainerView.hh"

#include "DataStructure/DataStructureManager.hh"
#include "DataStructure/Vec3BufferData.hh"
#include "DataStructure/TextureData.hh"
#include "DataStructure/Mat4Data.hh"

#include <assert.h>

DataStructureEditor::DataStructureEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataStructureEditor)
{
    ui->setupUi(this);

    _containerView = new ContainerView(this);

    _addSon = false;
    _removeSon = false;

    _isAddingSon = false;
    _isRemovingSon = false;

    _dataTypes.append("data container (empty data structure)");
//    _dataTypes.append("float vertex buffer (draw call)");
//    _dataTypes.append("vec2 vertex buffer (draw call)");
    _dataTypes.append("vec3 vertex buffer (draw call)");
//    _dataTypes.append("vec4 vertex buffer (draw call)");
    _dataTypes.append("texture (sampler 2D / render texture)");
//    _dataTypes.append("float");
//    _dataTypes.append("int");
//    _dataTypes.append("uint");
//    _dataTypes.append("vec2");
//    _dataTypes.append("vec3");
//    _dataTypes.append("vec4");
//    _dataTypes.append("int vec2");
//    _dataTypes.append("int vec3");
//    _dataTypes.append("int vec4");
//    _dataTypes.append("uint vec2");
//    _dataTypes.append("uint vec3");
//    _dataTypes.append("uint vec4");
//    _dataTypes.append("mat2 (2D rotation and scale)");
//    _dataTypes.append("mat3 (3D rotation and scale / 2D transform)");
    _dataTypes.append("mat4 (3D transform / projection)");

    ui->dataTypes->addItems(_dataTypes);

    QObject::connect(ui->createData, SIGNAL(released()),
                     this, SLOT(createData()));
    QObject::connect(ui->deleteData, SIGNAL(released()),
                     this, SLOT(deleteData()));
    QObject::connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                     this, SLOT(selectionChanged()));
}

DataStructureEditor::~DataStructureEditor()
{
    delete ui;
}

void DataStructureEditor::createData()
{
    SInstance *dataToAdd;

    switch (ui->dataTypes->currentIndex())
    {
    case 0:
        dataToAdd = new SContainerInstance();
        break;
    case 1:
        dataToAdd = new SDataInstance(new Vec3BufferData());
        break;
    case 2:
        dataToAdd = new SDataInstance(new TextureData());
        break;
    case 3:
        dataToAdd = new SDataInstance(new Mat4Data());
        break;
    default:
        assert(!"Not implemented yet!");
        break;
    }
    DataStructureManager::getManager()->addData(dataToAdd);
    QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget);

    item->setText(0, dataToAdd->getName());
    ui->treeWidget->addTopLevelItem(item);
}

void DataStructureEditor::deleteData()
{
    // Remove widget
    QLayoutItem *item = ui->dataViewGrid->takeAt(0);
    item->widget()->setParent(NULL);
    delete item;
    // Remove current data
    SInstance *current = DataStructureManager::getManager()->getCurrent();
    DataStructureManager::getManager()->removeCurrent();
    current->destroy();
    delete current;
    // Remove from tree view
    QTreeWidgetItem *toRemove = ui->treeWidget->currentItem();
    if (toRemove->parent())
    {
        toRemove = toRemove->parent()->takeChild(toRemove->parent()->indexOfChild(toRemove));
    }
    else
    {
        toRemove = ui->treeWidget->takeTopLevelItem(ui->treeWidget->indexOfTopLevelItem(toRemove));
    }
    delete toRemove;
}

void DataStructureEditor::selectionChanged()
{
    if (_isAddingSon || _isRemovingSon)
        return;
    if (ui->treeWidget->currentItem() != NULL)
    {
        if (_addSon) // We add a son to the container
        {
            _isAddingSon = true;

            // Change hierarchy in data structure
            QString currentItemName = ui->treeWidget->currentItem()->text(0);
            SInstance *selected = DataStructureManager::getManager()->getData(currentItemName);
            SContainerInstance *container = static_cast<SContainerInstance*>(DataStructureManager::getManager()->getCurrent());

            DataStructureManager::getManager()->removeData(selected);
            container->addSon(selected);

            // Change hierarchy in tree view
            QModelIndex idx = ui->treeWidget->currentIndex();
            QTreeWidgetItem *toMove = ui->treeWidget->currentItem();

            if (toMove->parent())
                toMove = toMove->parent()->takeChild(toMove->parent()->indexOfChild(toMove));
            else
                toMove = ui->treeWidget->takeTopLevelItem(idx.row());

            _currentSelection->addChild(toMove);
            ui->treeWidget->setCurrentItem(_currentSelection);

            _addSon = false;
            _isAddingSon = false;
            emit sonAdded(false);
        }
        else if (_removeSon) // We remove a son from the container
        {
            _isRemovingSon = true;

            QTreeWidgetItem *toMove = ui->treeWidget->currentItem();

            if (toMove->parent() == _currentSelection)
            {
                // Change in data structure
                SInstance *toMoveData = DataStructureManager::getManager()->getData(toMove->text(0));
                SContainerInstance *father = toMoveData->getParent();
                // Remove it from manager and put it one level higher
                father->removeSon(toMoveData);
                father->getParent()->addSon(toMoveData);

                // Change it in the view
                toMove = toMove->parent()->takeChild(_currentSelection->indexOfChild(toMove));
                if (_currentSelection->parent())
                {
                    _currentSelection->parent()->addChild(toMove);
                }
                else
                {
                    ui->treeWidget->addTopLevelItem(toMove);
                }
            }
            ui->treeWidget->setCurrentItem(_currentSelection);

            _removeSon = false;
            _isRemovingSon = false;
            emit sonRemoved(false);
        }
        else // We change the selection
        {
            _currentSelection = ui->treeWidget->currentItem();
            ui->deleteData->setEnabled(true);
            SInstance *oldCurrent = DataStructureManager::getManager()->getCurrent();
            // Remove the old widget
            if (oldCurrent)
            {
                QLayoutItem *item = ui->dataViewGrid->takeAt(0);
                item->widget()->setParent(NULL);
                delete item;
            }
            QString selectedName = ui->treeWidget->currentItem()->text(0);
            SInstance *current = DataStructureManager::getManager()->getData(selectedName);
            DataStructureManager::getManager()->setCurrent(current);
            if (current->getType() == DATA_INSTANCE)
            {
                ui->dataViewGrid->addWidget(static_cast<SDataInstance*>(current)->getData()->getView());
            }
            else
            {
                ui->dataViewGrid->addWidget(_containerView);
            }
        }
    }
    else
    {
        _currentSelection = ui->treeWidget->currentItem();
        SInstance *oldCurrent = DataStructureManager::getManager()->getCurrent();
        if (oldCurrent)
        {
            QLayoutItem *item = ui->dataViewGrid->takeAt(0);
            item->widget()->setParent(NULL);
            delete item;
        }
        DataStructureManager::getManager()->setCurrentNull();
        ui->deleteData->setEnabled(false);
    }
}

void DataStructureEditor::setAddSon()
{
    _addSon = !_addSon;
}

void DataStructureEditor::setRemoveSon()
{
    _removeSon = !_removeSon;
}

