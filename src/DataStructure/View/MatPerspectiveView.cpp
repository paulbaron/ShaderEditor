#include "MatPerspectiveView.hh"
#include "ui_MatPerspectiveView.h"

#include <glm/gtc/matrix_transform.hpp>

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
