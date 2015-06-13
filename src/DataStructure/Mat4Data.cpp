#include "Mat4Data.hh"
#include "View/Mat4DataView.hh"
#include "ui_Mat4DataView.h"

#include "View/Mat3DTransformView.hh"
#include "View/Mat3DLookAtView.hh"
#include "View/MatPerspectiveView.hh"
#include "ui_Mat3DTransformView.h"
#include "ui_Mat3DLookAtView.h"
#include "ui_MatPerspectiveView.h"

#include <../vendors/glm/gtc/matrix_transform.hpp>

Mat4Data::Mat4Data()
{
    _type = DATA_MAT4;
    _view = new Mat4DataView(this);
}

Mat4Data::~Mat4Data()
{

}

void Mat4Data::saveChanges()
{
    Mat4DataView *matView = static_cast<Mat4DataView*>(_view);

    switch (matView->getMatrixType())
    {
    case Mat4DataView::Transform:
        {
            Ui::Mat3DTransformView *ui = static_cast<Mat3DTransformView*>(matView->getCurrent())->getUi();
            glm::vec3 position, rotation, scale;

            position = glm::vec3(ui->posX->value(), ui->posY->value(), ui->posZ->value());
            rotation = glm::vec3(ui->rotX->value(), ui->rotY->value(), ui->rotZ->value());
            scale = glm::vec3(ui->scaleX->value(), ui->scaleY->value(), ui->scaleZ->value());

            _matrix = glm::translate(glm::mat4(1), position);
            _matrix = glm::rotate(_matrix, rotation.x, glm::vec3(1, 0, 0));
            _matrix = glm::rotate(_matrix, rotation.y, glm::vec3(0, 1, 0));
            _matrix = glm::rotate(_matrix, rotation.z, glm::vec3(0, 0, 1));
            _matrix = glm::scale(_matrix, scale);
        }
        break;
    case Mat4DataView::LookAt:
        {
            Ui::Mat3DLookAtView *ui = static_cast<Mat3DLookAtView*>(matView->getCurrent())->getUi();
            glm::vec3 eye, center, up;

            eye = glm::vec3(ui->eyeX->value(), ui->eyeY->value(), ui->eyeZ->value());
            center = glm::vec3(ui->centerX->value(), ui->centerY->value(), ui->centerZ->value());
            up = glm::vec3(ui->upX->value(), ui->upY->value(), ui->upZ->value());

            _matrix = glm::lookAt(eye, center, up);
        }
        break;
    case Mat4DataView::Perspective:
        {
            Ui::MatPerspectiveView *ui = static_cast<MatPerspectiveView*>(matView->getCurrent())->getUi();

            _matrix = glm::perspectiveFov(ui->fov->value(), ui->width->value(), ui->height->value(),
                                          ui->near->value(), ui->far->value());
        }
        break;
    default:
        break;
    }
    if (matView->getUi()->invertCheckBox->isChecked())
        _matrix = glm::inverse(_matrix);
}
