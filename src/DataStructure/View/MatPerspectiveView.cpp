#include "MatPerspectiveView.hh"
#include "ui_MatPerspectiveView.h"

#include <vendors/glm/gtc/matrix_transform.hpp>

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

glm::mat4 MatPerspectiveView::getPerspective() const
{
    return (glm::perspectiveFov(ui->fov->value(), ui->width->value(),ui->height->value(),
                                ui->near->value(), ui->far->value()));
}
