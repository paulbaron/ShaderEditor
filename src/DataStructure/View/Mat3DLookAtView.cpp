#include "Mat3DLookAtView.hh"
#include "ui_Mat3DLookAtView.h"

Mat3DLookAtView::Mat3DLookAtView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mat3DLookAtView)
{
    ui->setupUi(this);
}

Mat3DLookAtView::~Mat3DLookAtView()
{
    delete ui;
}

Ui::Mat3DLookAtView *Mat3DLookAtView::getUi() const
{
    return (ui);
}
