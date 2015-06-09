#include "DataStructureEditor.hh"
#include "ui_DataStructureEditor.h"

#include "DataStructure/DataStructureManager.hh"
#include "DataStructure/ContainerData.hh"
#include "DataStructure/TextureData.hh"

DataStructureEditor::DataStructureEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DataStructureEditor)
{
    ui->setupUi(this);

    _dataTypes.append("data container (empty data structure)");
    _dataTypes.append("float vertex buffer (draw call)");
    _dataTypes.append("vec2 vertex buffer (draw call)");
    _dataTypes.append("vec3 vertex buffer (draw call)");
    _dataTypes.append("vec4 vertex buffer (draw call)");
    _dataTypes.append("texture (sampler 2D / render texture)");
    _dataTypes.append("float");
    _dataTypes.append("int");
    _dataTypes.append("uint");
    _dataTypes.append("vec2");
    _dataTypes.append("vec3");
    _dataTypes.append("vec4");
    _dataTypes.append("int vec2");
    _dataTypes.append("int vec3");
    _dataTypes.append("int vec4");
    _dataTypes.append("uint vec2");
    _dataTypes.append("uint vec3");
    _dataTypes.append("uint vec4");
    _dataTypes.append("mat2 (2D rotation and scale)");
    _dataTypes.append("mat3 (3D rotation and scale / 2D transform)");
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
    switch (ui->dataTypes->currentIndex())
    {
    case 0:
        DataStructureManager::getManager()->addData(new ContainerData());
        break;
    case 5:
        DataStructureManager::getManager()->addData(new TextureData());
        break;
    default:
        assert(!"Not implemented yet!");
        break;
    }
}

void DataStructureEditor::deleteData()
{
    ui->treeWidget->take
}

void DataStructureEditor::selectionChanged()
{
    if (ui->treeWidget->currentItem() != NULL)
    {
        ui->deleteData->setEnabled(true);
        int currentColumn = ui->treeWidget->currentColumn();
        DataStructureManager::getManager()->setCurrent(ui->treeWidget->currentItem()->text(currentColumn));
        ui->dataViewGrid->addWidget();
    }
    else
    {
        ui->deleteData->setEnabled(false);
    }
}
