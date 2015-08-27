#include "DataStructureEditor.hh"
#include "ui_DataStructureEditor.h"
#include "ui_RenderPassUi.h"

#include "RenderPassManager.hh"
#include "DataStructure/View/ContainerView.hh"

#include "DataStructure/DataStructureManager.hh"
#include "DataStructure/Vec2BufferData.hh"
#include "DataStructure/Vec3BufferData.hh"
#include "DataStructure/IndexBufferData.hh"
#include "DataStructure/RenderTextureData.hh"
#include "DataStructure/LoadedTextureData.hh"
#include "DataStructure/Mat4Data.hh"
#include "DataStructure/VecData.hpp"

#include <assert.h>

DataStructureEditor::DataStructureEditor(RenderPassUi *renderPassui, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataStructureEditor)
{
    ui->setupUi(this);

    _containerView = new ContainerView(this);

    _addSon = false;
    _removeSon = false;

    _isAddingSon = false;
    _isRemovingSon = false;

    _dataTypes.append("Data Container (Empty Data Structure)");
    _dataTypes.append("Vec2 Vertex Buffer (Draw Call)");
    _dataTypes.append("Vec3 Vertex Buffer (Draw Call)");
    _dataTypes.append("Index Buffer (Draw Call)");
    _dataTypes.append("Render Texture (Sampler 2D / Output Texture)");
    _dataTypes.append("Loaded Texture (Sampler 2D)");
    _dataTypes.append("Float");
    _dataTypes.append("Vec2");
    _dataTypes.append("Vec3");
    _dataTypes.append("Vec4");
    _dataTypes.append("Mat4 (3D Transform / Projection)");

    _renderPassUi = renderPassui;

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

void DataStructureEditor::reloadUi()
{
    _addSon = false;
    _removeSon = false;
    _isAddingSon = false;
    _isRemovingSon = false;
    ui->deleteData->setEnabled(false);
    ui->treeWidget->clear();
    // Remove widget
    QLayoutItem *item = ui->dataViewGrid->takeAt(0);
    if (item != NULL)
    {
        item->widget()->setParent(NULL);
        delete item;
    }
    for (QList<SInstance*>::const_iterator it =
            DataStructureManager::getManager()->getRoot().begin();
         it != DataStructureManager::getManager()->getRoot().end();
         ++it)
    {
        ui->treeWidget->addTopLevelItem((*it)->getTreeItem());
    }
}

void DataStructureEditor::createData()
{
    SInstance *dataAdded;

    switch (ui->dataTypes->currentIndex())
    {
    case 0:
        dataAdded = DataStructureManager::getManager()->addContainer();
        break;
    case 1:
        dataAdded = DataStructureManager::getManager()->addData(new Vec2BufferData);
        break;
    case 2:
        dataAdded = DataStructureManager::getManager()->addData(new Vec3BufferData);
        break;
    case 3:
        dataAdded = DataStructureManager::getManager()->addData(new IndexBufferData);
        break;
    case 4:
        dataAdded = DataStructureManager::getManager()->addData(new RenderTextureData);
        break;
    case 5:
        dataAdded = DataStructureManager::getManager()->addData(new LoadedTextureData);
        break;
    case 6:
        dataAdded = DataStructureManager::getManager()->addData(new VecData<glm::vec1>);
        break;
    case 7:
        dataAdded = DataStructureManager::getManager()->addData(new VecData<glm::vec2>);
        break;
    case 8:
        dataAdded = DataStructureManager::getManager()->addData(new VecData<glm::vec3>);
        break;
    case 9:
        dataAdded = DataStructureManager::getManager()->addData(new VecData<glm::vec4>);
        break;
    case 10:
        dataAdded = DataStructureManager::getManager()->addData(new Mat4Data());
        break;
    default:
        assert(!"Not implemented yet!");
        break;
    }
    QTreeWidgetItem *item = dataAdded->getTreeItem();

    ui->treeWidget->addTopLevelItem(item);
}

void DataStructureEditor::deleteData()
{
    // Remove widget
    QLayoutItem *item = ui->dataViewGrid->takeAt(0);
    item->widget()->setParent(NULL);
    delete item;
    SInstance *current = DataStructureManager::getManager()->getCurrent();
    recursiveDeleteDataFromRenderPass(current);
    // Remove current data
    DataStructureManager::getManager()->removeCurrent();
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
            int currentItemId = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt();
            SInstance *selected = DataStructureManager::getManager()->getInstance(currentItemId);
            SContainerInstance *container = static_cast<SContainerInstance*>(DataStructureManager::getManager()->getCurrent());

            DataStructureManager::getManager()->removeInstance(selected);
            container->addSon(selected);

            // Change hierarchy in tree view
            QModelIndex idx = ui->treeWidget->currentIndex();
            QTreeWidgetItem *toMove = ui->treeWidget->currentItem();

            if (toMove->parent())
                toMove = toMove->parent()->takeChild(toMove->parent()->indexOfChild(toMove));
            else
                toMove = ui->treeWidget->takeTopLevelItem(idx.row());

            _currentSelection->addChild(toMove);

            ui->treeWidget->clearSelection();
            ui->treeWidget->setCurrentItem(_currentSelection);

            _addSon = false;
            _isAddingSon = false;
            emit sonAdded(false);
        }
        else if (_removeSon) // We remove a son from the container
        {
            _isRemovingSon = true;

            QTreeWidgetItem *toMove = ui->treeWidget->currentItem();

            // Change in data structure
            SInstance *toMoveData = DataStructureManager::getManager()->getInstance(toMove->data(0, Qt::UserRole).toInt());
            SContainerInstance *father = toMoveData->getParent();
            // Remove it from manager and put it one level higher
            if (father->removeSon(toMoveData))
            {
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
            ui->treeWidget->clearSelection();
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
            int selectedId = ui->treeWidget->currentItem()->data(0, Qt::UserRole).toInt();
            SInstance *current = DataStructureManager::getManager()->getInstance(selectedId);
            DataStructureManager::getManager()->setCurrent(selectedId);
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

void DataStructureEditor::recursiveDeleteDataFromRenderPass(SInstance *data)
{
    if (data->getType() == DATA_INSTANCE)
    {
        SDataInstance *current = static_cast<SDataInstance*>(data);
        // Remove from Render Passes
        RenderPassManager::getManager()->removeData(current->getData());
        // Remove from the UI inputs of the render pass
        QTreeWidget *renderPassTreeWidget = _renderPassUi->getUi()->treeWidget;
        QList<QTreeWidgetItem*> inputToRemove = renderPassTreeWidget->findItems(
                                current->getData()->getName(),
                                Qt::MatchContains | Qt::MatchRecursive);
        for (QList<QTreeWidgetItem*>::const_iterator it = inputToRemove.begin();
             it != inputToRemove.end();
             ++it)
        {
            if ((*it)->parent() != NULL)
            {
                (*it)->parent()->takeChild((*it)->parent()->indexOfChild(*it));
            }
            else
            {
                renderPassTreeWidget->takeTopLevelItem(renderPassTreeWidget->indexOfTopLevelItem(*it));
            }
            delete *it;
        }
    }
    else if (data->getType() == CONTAINER_INSTANCE)
    {
        SContainerInstance *current = static_cast<SContainerInstance*>(data);
        for (QList<SInstance*>::const_iterator it = current->begin();
             it != current->end();
             ++it)
        {
            recursiveDeleteDataFromRenderPass(*it);
        }
    }
}
