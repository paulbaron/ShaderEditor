#include "MatPerspectiveView.hh"
#include "ui_MatPerspectiveView.h"

MatPerspectiveView::MatPerspectiveView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MatPerspectiveView)
{
    ui->setupUi(this);
}

MatPerspectiveView::~MatPerspectiveView()
{
    delete ui;
}

Ui::MatPerspectiveView *MatPerspectiveView::getUi() const
{
    return (ui);
}
