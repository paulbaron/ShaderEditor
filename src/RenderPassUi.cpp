#include "RenderPassUi.h"
#include "ui_renderpassui.h"

#include "RenderPassView.hh"

RenderPassUi::RenderPassUi(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RenderPassUi)
{
    ui->setupUi(this);

    ui->verticalLayout->addWidget(new RenderPassView());
    QObject::connect(ui->vertexCodeEdit, SIGNAL(textChanged(void)),
                     this, SLOT(setCurrentVertexShader(void)));
    QObject::connect(ui->fragmentCodeEdit, SIGNAL(textChanged(void)),
                     this, SLOT(setCurrentFragmentShader(void)));
}

RenderPassUi::~RenderPassUi()
{
    delete ui;
}

void RenderPassUi::setCurrentVertexShader()
{
    QString shaderCode = ui->vertexCodeEdit->toPlainText();
}

void RenderPassUi::setCurrentFragmentShader()
{
    QString shaderCode = ui->fragmentCodeEdit->toPlainText();
}
