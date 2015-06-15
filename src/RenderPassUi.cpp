#include "RenderPassUi.h"
#include "ui_renderpassui.h"

#include "RenderPassView.hh"
#include "DataStructure/DataStructureManager.hh"
#include "RenderPassManager.hh"

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

    ui->inputName->setInputMask("nnnnnnnnnnnnnnnnnnnnnnnn");

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
    QObject::connect(ui->inputName, SIGNAL(textEdited(QString)),
                    this, SLOT(inputNameChanged()));
    // Output
    QObject::connect(ui->tableWidget, SIGNAL(currentCellChanged(int,int,int,int)),
                     this, SLOT(selectedOutputChanged()));
    QObject::connect(ui->setOutput, SIGNAL(released()),
                     this, SLOT(setOutput()));
    QObject::connect(ui->unsetOutput, SIGNAL(released()),
                     this, SLOT(unsetOutput()));
    QObject::connect(DataStructureManager::getManager(), SIGNAL(textureChangedType()),
                     this, SLOT(checkEnableOutput()));
}

RenderPassUi::~RenderPassUi()
{
    delete ui;
}

void RenderPassUi::createRenderPass()
{

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
        checkEnableOutput();
        ui->instantiate->setEnabled(true);
    }
}

void RenderPassUi::instantiate()
{
    SInstance *instance = DataStructureManager::getManager()->getCurrent()->copy();

    RenderPassManager::getManager()->getCurrent()->setInput(instance);
    ui->treeWidget->addTopLevelItem(instance->getTreeItem());
}

void RenderPassUi::removeInstance()
{
    RenderPassManager::getManager()->getCurrent()->removeCurrentInput();
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
        int currentInputId = newCurrent->data(0, Qt::UserRole).toInt();
        currentInstance = RenderPassManager::getManager()->getCurrent()->getInput(currentInputId);
        RenderPassManager::getManager()->getCurrent()->setCurrentInput(currentInstance);

        ui->removeInstance->setEnabled(true);
        if (currentInstance->getType() != CONTAINER_INSTANCE)
        {
            SDataInstance *dataInstance = static_cast<SDataInstance*>(currentInstance);

            ui->inputName->setEnabled(true);
            ui->inputName->setText(dataInstance->getInputName());
        }
        else
        {
            ui->addSon->setEnabled(true);
            ui->removeSon->setEnabled(true);
            ui->inputName->setEnabled(false);
            ui->inputName->setText("");
        }
    }
    else
    {
        ui->addSon->setEnabled(false);
        ui->removeSon->setEnabled(false);
        ui->removeInstance->setEnabled(false);
        ui->inputName->setEnabled(false);
        ui->inputName->setText("");
    }
}

void RenderPassUi::createGroup()
{
    SContainerInstance *toAdd = new SContainerInstance;

    ui->treeWidget->addTopLevelItem(toAdd->getTreeItem());
    RenderPassManager::getManager()->getCurrent()->setInput(toAdd);
}

void RenderPassUi::addSon()
{
    _addSon = true;
}

void RenderPassUi::removeSon()
{
    _removeSon = true;
}

void RenderPassUi::inputNameChanged()
{
    SDataInstance *currentInput = static_cast<SDataInstance*>(RenderPassManager::getManager()->getCurrent()->getCurrentInput());
    QString newName = ui->inputName->text();

    newName.replace(" ", "");
    if (newName == "")
    {
        newName = "uniformData";
    }
    currentInput->setInputName(newName);
    ui->treeWidget->currentItem()->setText(1, newName);
}

void RenderPassUi::selectedOutputChanged()
{
    checkEnableOutput();
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
    RenderPass::EOutputs attachment = static_cast<RenderPass::EOutputs>(ui->tableWidget->currentRow());
    SDataInstance *dataInst = static_cast<SDataInstance*>(DataStructureManager::getManager()->getCurrent());
    TextureData *texture = static_cast<TextureData*>(dataInst->getData());
    QTableWidgetItem *item;

    RenderPassManager::getManager()->getCurrent()->setOutput(attachment, texture);
    item = ui->tableWidget->item(ui->tableWidget->currentRow(), 0);
    if (item == NULL)
    {
        item = new QTableWidgetItem(texture->getName());
        ui->tableWidget->setItem(ui->tableWidget->currentRow(), 0, item);
    }
    item->setText(dataInst->getName());
}

void RenderPassUi::unsetOutput()
{
    RenderPass::EOutputs attachment = static_cast<RenderPass::EOutputs>(ui->tableWidget->currentRow());

    RenderPassManager::getManager()->getCurrent()->unsetOutput(attachment);
    ui->tableWidget->item(ui->tableWidget->currentRow(), 0)->setText("");
}

void RenderPassUi::setCurrentVertexShader()
{
    QString shaderCode = ui->vertexCodeEdit->toPlainText();
    RenderPassManager::getManager()->getCurrent()->setVertexCode(shaderCode);
}

void RenderPassUi::setCurrentFragmentShader()
{
    QString shaderCode = ui->fragmentCodeEdit->toPlainText();
    RenderPassManager::getManager()->getCurrent()->setFragmentCode(shaderCode);
}

void RenderPassUi::checkEnableOutput()
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
