#include "RenderPassUi.h"
#include "ui_renderpassui.h"

#include "RenderPassView.hh"
#include "DataStructure/DataStructureManager.hh"

RenderPassUi::RenderPassUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderPassUi)
{
    ui->setupUi(this);

    _addSon = false;
    _removeSon = false;
    _isAddingSon = false;
    _isRemovingSon = false;

    ui->renderPassDisplay->addWidget(new RenderPassView());

    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);

    QObject::connect(ui->createRenderPass, SIGNAL(released()),
                     this, SLOT(createRenderPass()));
    QObject::connect(DataStructureManager::getManager(), SIGNAL(currentSelectionChanged(SInstance*)),
                     this, SLOT(selectedDataChanged(SInstance*)));
    // Shaders
    QObject::connect(ui->vertexCodeEdit, SIGNAL(textChanged(void)),
                     this, SLOT(setCurrentVertexShader(void)));
    QObject::connect(ui->fragmentCodeEdit, SIGNAL(textChanged(void)),
                     this, SLOT(setCurrentFragmentShader(void)));
    // Inputs
    QObject::connect(ui->instantiate, SIGNAL(released()),
                    this, SLOT(instantiate()));
    QObject::connect(ui->removeInstance, SIGNAL(released()),
                     this, SLOT(removeInstance()));
    QObject::connect(ui->treeWidget, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
                     this, SLOT(selectedInputChanged()));
    QObject::connect(ui->createGroup, SIGNAL(released()),
                     this, SLOT(createGroup()));
    QObject::connect(ui->addSon, SIGNAL(released()),
                     this, SLOT(addSon()));
    QObject::connect(ui->removeSon, SIGNAL(released()),
                     this, SLOT(removeSon()));
    // Output
    QObject::connect(ui->tableWidget, SIGNAL(currentCellChanged(int,int,int,int)),
                     this, SLOT(selectedOutputChanged()));
    QObject::connect(ui->setOutput, SIGNAL(released()),
                     this, SLOT(setOutput()));
    QObject::connect(ui->unsetOutput, SIGNAL(released()),
                     this, SLOT(unsetOutput()));
}

RenderPassUi::~RenderPassUi()
{
    delete ui;
}

void RenderPassUi::createRenderPass()
{
    _currentPass = new RenderPass;
}

void RenderPassUi::selectedDataChanged(SInstance *current)
{
    if (current == NULL)
    {
        ui->instantiate->setEnabled(false);
        ui->setOutput->setEnabled(false);
    }
    else
    {
        enableOutput();
        ui->instantiate->setEnabled(true);
    }
}

void RenderPassUi::instantiate()
{
    SInstance *instance = DataStructureManager::getManager()->getCurrent()->copy();

    _currentPass->setInput(instance);
    ui->treeWidget->addTopLevelItem(instance->getTreeItem());
}

void RenderPassUi::removeInstance()
{
    _currentPass->removeCurrentInput();
    QModelIndex idx = ui->treeWidget->currentIndex();
    QTreeWidgetItem *toRm = ui->treeWidget->currentItem();

    if (toRm->parent() != NULL)
    {
        toRm = toRm->parent()->takeChild(toRm->parent()->indexOfChild(toRm));
    }
    else
    {
        toRm = ui->treeWidget->takeTopLevelItem(idx.row());
    }
    delete toRm;
}

void RenderPassUi::selectedInputChanged()
{
    QTreeWidgetItem *newCurrent = ui->treeWidget->currentItem();
    SInstance *currentInstance = NULL;

    if (newCurrent)
    {
        currentInstance = _currentPass->getInput(newCurrent->text(0));
        _currentPass->setCurrentInput(currentInstance);

        ui->removeInstance->setEnabled(true);
    }
    else
    {
        ui->removeInstance->setEnabled(false);
    }
    if (currentInstance != NULL &&
        currentInstance->getType() == CONTAINER_INSTANCE)
    {
        ui->addSon->setEnabled(true);
        ui->removeSon->setEnabled(true);
    }
    else
    {
        ui->addSon->setEnabled(false);
        ui->removeSon->setEnabled(false);
    }
}

void RenderPassUi::createGroup()
{
    SContainerInstance *toAdd = new SContainerInstance;

    ui->treeWidget->addTopLevelItem(toAdd->getTreeItem());
    _currentPass->setInput(toAdd);
}

void RenderPassUi::addSon()
{
    _addSon = true;
}

void RenderPassUi::removeSon()
{
    _removeSon = true;
}

void RenderPassUi::selectedOutputChanged()
{
    enableOutput();
    if (ui->tableWidget->currentItem() &&
        ui->tableWidget->currentItem()->text() != "")
    {
        ui->unsetOutput->setEnabled(true);
    }
    else
    {
        ui->unsetOutput->setEnabled(false);
    }
}

void RenderPassUi::setOutput()
{

}

void RenderPassUi::unsetOutput()
{

}

void RenderPassUi::setCurrentVertexShader()
{
    QString shaderCode = ui->vertexCodeEdit->toPlainText();
    _currentPass->setVertexCode(shaderCode);
}

void RenderPassUi::setCurrentFragmentShader()
{
    QString shaderCode = ui->fragmentCodeEdit->toPlainText();
    _currentPass->setFragmentCode(shaderCode);
}

void RenderPassUi::enableOutput()
{
    SInstance *current = DataStructureManager::getManager()->getCurrent();


    if (current != NULL &&
        ui->tableWidget->currentRow() != -1 &&
        current->getType() == DATA_INSTANCE)
    {
        SDataInstance *dataInst = static_cast<SDataInstance*>(current);

        if (dataInst->getData()->getType() == AbstractData::DATA_TEXTURE)
        {
            TextureData *texture = static_cast<TextureData*>(dataInst->getData());

            switch (ui->tableWidget->currentRow())
            {
            case 0:
                if (texture->getInternalFormat() == GL_DEPTH_COMPONENT16 ||
                    texture->getInternalFormat() == GL_DEPTH_COMPONENT24 ||
                    texture->getInternalFormat() == GL_DEPTH_COMPONENT32)
                {
                    ui->setOutput->setEnabled(true);
                }
                else
                {
                    ui->setOutput->setEnabled(false);
                }
                break;
            case 1:
                if (texture->getInternalFormat() == GL_DEPTH24_STENCIL8)
                {
                    ui->setOutput->setEnabled(true);
                }
                else
                {
                    ui->setOutput->setEnabled(false);
                }
                break;
            default:
                if (texture->getInternalFormat() != GL_DEPTH_COMPONENT16 &&
                    texture->getInternalFormat() != GL_DEPTH_COMPONENT24 &&
                    texture->getInternalFormat() != GL_DEPTH_COMPONENT32 &&
                    texture->getInternalFormat() != GL_DEPTH24_STENCIL8)
                {
                    ui->setOutput->setEnabled(true);
                }
                else
                {
                    ui->setOutput->setEnabled(false);
                }
                break;
            }
        }
        else
        {
            ui->setOutput->setEnabled(false);
        }
    }
    else
    {
        ui->setOutput->setEnabled(false);
    }
}
