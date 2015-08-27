#include "BaseVecView.hh"
#include "ui_BaseVecView.h"

BaseVecView::BaseVecView(AbstractData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BaseVecView)
{
    ui->setupUi(this);

    QObject::connect(ui->saveChanges, SIGNAL(released()),
                     data, SLOT(saveChanges()));
}

BaseVecView::~BaseVecView()
{
    delete ui;
}
