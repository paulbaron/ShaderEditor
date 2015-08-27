#include "Mat4Data.hh"
#include "ui_Mat4DataView.h"

#include "View/Mat3DTransformView.hh"
#include "View/Mat3DLookAtView.hh"
#include "View/MatPerspectiveView.hh"
#include "ui_MatPerspectiveView.h"
#include "ui_Mat3DTransformView.h"
#include "ui_Mat3DLookAtView.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

BOOST_CLASS_EXPORT_IMPLEMENT(Mat4Data)

Mat4Data::Mat4Data() :
    AbstractData("Mat4_")
{
    _type = DATA_MAT4;
    _view = new Mat4DataView(this);
    _matType = Mat4DataView::Transform;
    saveChanges();
}

Mat4Data::~Mat4Data()
{

}

QString Mat4Data::getInputType() const
{
    return ("uniform mat4");
}

void Mat4Data::setInput(QString inputName, GLSLShader &program, int textureBinding)
{
    program.setUniform(inputName, _matrix);
}

void Mat4Data::saveChanges()
{
    Mat4DataView *matView = static_cast<Mat4DataView*>(_view);

    _matType = matView->getMatrixType();
    switch (_matType)
    {
    case Mat4DataView::Transform:
        {
            Ui::Mat3DTransformView *ui = static_cast<Mat3DTransformView*>(matView->getCurrent())->getUi();

            _position = glm::vec3(ui->posX->value(), ui->posY->value(), ui->posZ->value());
            _rotation = glm::vec3(ui->rotX->value(), ui->rotY->value(), ui->rotZ->value());
            _scale = glm::vec3(ui->scaleX->value(), ui->scaleY->value(), ui->scaleZ->value());

            _matrix = glm::translate(glm::mat4(1), _position);
            _matrix = glm::rotate(_matrix, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
            _matrix = glm::rotate(_matrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
            _matrix = glm::rotate(_matrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
            _matrix = glm::scale(_matrix, _scale);
        }
        break;
    case Mat4DataView::LookAt:
        {
            Ui::Mat3DLookAtView *ui = static_cast<Mat3DLookAtView*>(matView->getCurrent())->getUi();

            _eye = glm::vec3(ui->eyeX->value(), ui->eyeY->value(), ui->eyeZ->value());
            _center = glm::vec3(ui->centerX->value(), ui->centerY->value(), ui->centerZ->value());
            _up = glm::vec3(ui->upX->value(), ui->upY->value(), ui->upZ->value());

            _matrix = glm::lookAt(_eye, _center, _up);
        }
        break;
    case Mat4DataView::Perspective:
        {
            Ui::MatPerspectiveView *ui = static_cast<MatPerspectiveView*>(matView->getCurrent())->getUi();

            _fov = static_cast<float>(ui->fov->value());
            _ratio.x = static_cast<float>(ui->width->value());
            _ratio.y = static_cast<float>(ui->height->value());
            _near = static_cast<float>(ui->nearDist->value());
            _far = static_cast<float>(ui->farDist->value());

            _matrix = glm::perspective(glm::radians(_fov), _ratio.x / _ratio.y, _near, _far);
        }
        break;
    default:
        break;
    }
    if (matView->getUi()->invertCheckBox->isChecked())
    {
        _matrix = glm::inverse(_matrix);
        _invert = true;
    }
    else
    {
        _invert = false;
    }
}

void Mat4Data::setUi()
{
    Mat4DataView *matView = static_cast<Mat4DataView*>(_view);

    switch (_matType)
    {
    case Mat4DataView::Transform:
        {
            matView->setTransform();
            Ui::Mat3DTransformView *ui = static_cast<Mat3DTransformView*>(matView->getCurrent())->getUi();

            ui->posX->setValue(_position.x);
            ui->posY->setValue(_position.y);
            ui->posZ->setValue(_position.z);

            ui->rotX->setValue(_rotation.x);
            ui->rotY->setValue(_rotation.y);
            ui->rotZ->setValue(_rotation.z);

            ui->scaleX->setValue(_scale.x);
            ui->scaleY->setValue(_scale.y);
            ui->scaleZ->setValue(_scale.z);

            _matrix = glm::translate(glm::mat4(1), _position);
            _matrix = glm::rotate(_matrix, glm::radians(_rotation.x), glm::vec3(1, 0, 0));
            _matrix = glm::rotate(_matrix, glm::radians(_rotation.y), glm::vec3(0, 1, 0));
            _matrix = glm::rotate(_matrix, glm::radians(_rotation.z), glm::vec3(0, 0, 1));
            _matrix = glm::scale(_matrix, _scale);
        }
        break;
    case Mat4DataView::LookAt:
        {
            matView->setLookAt();
            Ui::Mat3DLookAtView *ui = static_cast<Mat3DLookAtView*>(matView->getCurrent())->getUi();

            ui->eyeX->setValue(_eye.x);
            ui->eyeY->setValue(_eye.y);
            ui->eyeZ->setValue(_eye.z);

            ui->centerX->setValue(_center.x);
            ui->centerY->setValue(_center.y);
            ui->centerZ->setValue(_center.z);

            ui->upX->setValue(_up.x);
            ui->upY->setValue(_up.y);
            ui->upZ->setValue(_up.z);

            _matrix = glm::lookAt(_eye, _center, _up);
        }
        break;
    case Mat4DataView::Perspective:
        {
            matView->setPerspective();
            Ui::MatPerspectiveView *ui = static_cast<MatPerspectiveView*>(matView->getCurrent())->getUi();

            ui->fov->setValue(_fov);
            ui->width->setValue(_ratio.x);
            ui->height->setValue(_ratio.y);
            ui->nearDist->setValue(_near);
            ui->farDist->setValue(_far);

            _matrix = glm::perspective(glm::radians(_fov), _ratio.x / _ratio.y, _near, _far);
        }
        break;
    default:
        break;
    }
    if (_invert)
    {
        matView->getUi()->invertCheckBox->setChecked(true);
        _matrix = glm::inverse(_matrix);
    }
    else
    {
        matView->getUi()->invertCheckBox->setChecked(false);
    }
}
