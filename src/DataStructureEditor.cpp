#include "DataStructureEditor.hh"
#include "ui_DataStructureEditor.h"

#include "DataStructure/DataStructureManager.hh"
#include "DataStructure/ContainerData.hh"
#include "DataStructure/Vec3BufferData.hh"
#include "DataStructure/TextureData.hh"
#include "DataStructure/Mat4Data.hh"

#include <assert.h>

DataStructureEditor::DataStructureEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataStructureEditor)
{
    ui->setupUi(this);

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
    AbstractData *dataToAdd;

    switch (ui->dataTypes->currentIndex())
    {
    case 0:
        dataToAdd = new ContainerData();
        break;
    case 1:
        dataToAdd = new Vec3BufferData();
        break;
    case 2:
        dataToAdd = new TextureData();
        break;
    case 3:
        dataToAdd = new Mat4Data();
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
    AbstractData *oldCurrent = DataStructureManager::getManager()->getCurrent();
    if (oldCurrent)
    {
        QLayoutItem *item = ui->dataViewGrid->takeAt(0);
        item->widget()->setParent(NULL);
        delete item;
    }
    // Remove current
    DataStructureManager::getManager()->removeCurrent();
    // Remove from tree
    QModelIndex idx = ui->treeWidget->currentIndex();
    QTreeWidgetItem *item = ui->treeWidget->takeTopLevelItem(idx.row());

    delete item;
}

void DataStructureEditor::selectionChanged()
{
    if (ui->treeWidget->currentItem() != NULL)
    {
        ui->deleteData->setEnabled(true);
        AbstractData *oldCurrent = DataStructureManager::getManager()->getCurrent();
        if (oldCurrent)
        {
            QLayoutItem *item = ui->dataViewGrid->takeAt(0);
            item->widget()->setParent(NULL);
            delete item;
        }
        QString selectedName = ui->treeWidget->currentItem()->text(0);
        AbstractData *current = DataStructureManager::getManager()->getData(selectedName);
        DataStructureManager::getManager()->setCurrent(current);
        if (current->getView() != NULL)
            ui->dataViewGrid->addWidget(current->getView());
    }
    else
    {
        AbstractData *oldCurrent = DataStructureManager::getManager()->getCurrent();
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
