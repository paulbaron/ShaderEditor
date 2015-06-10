#include "ContainerView.hh"
#include "ui_ContainerView.h"

ContainerView::ContainerView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ContainerView)
{
    ui->setupUi(this);
}

ContainerView::~ContainerView()
{
    delete ui;
}
