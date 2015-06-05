#include "RenderPassUi.h"
#include "ui_renderpassui.h"

#include "RenderPassView.hh"

RenderPassUi::RenderPassUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderPassUi)
{
    ui->setupUi(this);

    ui->verticalLayout->addWidget(new RenderPassView());
}

RenderPassUi::~RenderPassUi()
{
    delete ui;
}
