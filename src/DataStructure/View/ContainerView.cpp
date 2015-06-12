#include "ContainerView.hh"
#include "ui_ContainerView.h"

ContainerView::ContainerView(bool &addSon, bool &removeSon, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContainerView),
    _addSon(addSon),
    _removeSon(removeSon)
{
    ui->setupUi(this);

    QObject::connect(ui->addSon, SIGNAL(released()),
                     this, SLOT(setAddSon()));
    QObject::connect(ui->removeSon, SIGNAL(released()),
                     this, SLOT(setRemoveSon()));

}

ContainerView::~ContainerView()
{
    delete ui;
}

void ContainerView::setAddSon()
{
    _addSon = !_addSon;
    ui->addSon->setChecked(_addSon);
}

void ContainerView::setRemoveSon()
{
    _removeSon = !_removeSon;
    ui->addSon->setChecked(_removeSon);
}
