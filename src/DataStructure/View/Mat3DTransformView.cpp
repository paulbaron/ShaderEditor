#include "Mat3DTransformView.hh"
#include "ui_Mat3DTransformView.h"

Mat3DTransformView::Mat3DTransformView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mat3DTransformView)
{
    ui->setupUi(this);
}

Mat3DTransformView::~Mat3DTransformView()
{
    delete ui;
}

Ui::Mat3DTransformView *Mat3DTransformView::getUi() const
{
    return (ui);
}
