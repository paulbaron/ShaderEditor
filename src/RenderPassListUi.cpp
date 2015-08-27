#include "RenderPassListUi.hh"
#include "ui_RenderPassListUi.h"
#include "ui_RenderPassUi.h"

#include "RenderPassManager.hh"

RenderPassListUi::RenderPassListUi(RenderPassUi *renderPassUi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderPassListUi)
{
    ui->setupUi(this);
    _renderPassUi = renderPassUi;

    QObject::connect(ui->renderPassList, SIGNAL(currentRowChanged(int)),
                     this, SLOT(RenderPassSelected()));
    QObject::connect(ui->createRenderPass, SIGNAL(released()),
                     this, SLOT(addRenderPass()));
}

RenderPassListUi::~RenderPassListUi()
{
    delete ui;
}

void RenderPassListUi::reloadUi()
{
    ui->renderPassList->clear();
    for (int i = 0; i < RenderPassManager::getManager()->getRenderPassCount(); ++i)
    {
        ui->renderPassList->addItem("Render Pass " + QString::number(i));
    }
}

void RenderPassListUi::addRenderPass()
{
    RenderPassManager::getManager()->createRenderPass();
    ui->renderPassList->addItem("Render Pass " +
                                QString::number(RenderPassManager::getManager()->getRenderPassCount()));
}

void RenderPassListUi::RenderPassSelected()
{
    QObject::disconnect(_renderPassUi->getUi()->treeWidget, SIGNAL(itemSelectionChanged()),
                     _renderPassUi, SLOT(selectedInputChanged()));
    int currentRenderPassId = ui->renderPassList->currentIndex().row();
    RenderPassManager::getManager()->setCurrent(currentRenderPassId, _renderPassUi->getUi());
    _renderPassUi->setEnabled(RenderPassManager::getManager()->getCurrent() != NULL);
    QObject::connect(_renderPassUi->getUi()->treeWidget, SIGNAL(itemSelectionChanged()),
                     _renderPassUi, SLOT(selectedInputChanged()));
}
