#include "Mat4DataView.hh"
#include "ui_Mat4DataView.h"

#include "Mat3DTransformView.hh"
#include "Mat3DLookAtView.hh"
#include "MatPerspectiveView.hh"

#include <assert.h>

Mat4DataView::Mat4DataView(AbstractData *data, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Mat4DataView)
{
    ui->setupUi(this);

    _current = NULL;
    setTransform();
    QObject::connect(ui->saveChanges, SIGNAL(released()),
                     data, SLOT(saveChanges()));
    QObject::connect(ui->matrixType, SIGNAL(currentIndexChanged(int)),
                     this, SLOT(matrixTypeChanged()));
}

Mat4DataView::~Mat4DataView()
{
    delete ui;
}

void Mat4DataView::setPerspective()
{
    QLayoutItem *layout = ui->editorLayout->takeAt(0);

    if (layout)
    {
        delete _current;
        delete layout;
    }
    _current = new MatPerspectiveView(this);
    ui->editorLayout->addWidget(_current);
    _type = Perspective;
}

void Mat4DataView::setTransform()
{
    QLayoutItem *layout = ui->editorLayout->takeAt(0);

    if (layout)
    {
        delete _current;
        delete layout;
    }
    _current = new Mat3DTransformView(this);
    ui->editorLayout->addWidget(_current);
    _type = Transform;
}

void Mat4DataView::setLookAt()
{
    QLayoutItem *layout = ui->editorLayout->takeAt(0);

    if (layout)
    {
        delete _current;
        delete layout;
    }
    _current = new Mat3DLookAtView(this);
    ui->editorLayout->addWidget(_current);
    _type = LookAt;
}

void Mat4DataView::matrixTypeChanged()
{
    switch (ui->matrixType->currentIndex())
    {
    case 0:
        setTransform();
        break;
    case 1:
        setLookAt();
        break;
    case 2:
        setPerspective();
        break;
    default:
        assert(!"Not implemented");
        break;
    }
}
