#include "Mat4DataView.hh"
#include "ui_Mat4DataView.h"

Mat4DataView::Mat4DataView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mat4DataView)
{
    ui->setupUi(this);
}

Mat4DataView::~Mat4DataView()
{
    delete ui;
}
