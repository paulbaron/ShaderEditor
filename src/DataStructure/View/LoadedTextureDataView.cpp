#include "LoadedTextureDataView.hh"
#include "ui_LoadedTextureDataView.h"

#include "EditorException.hh"

#include <QFileDialog>

LoadedTextureDataView::LoadedTextureDataView(LoadedTextureData *textureData, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LoadedTextureDataView)
{
    ui->setupUi(this);

    _filterModes.append("LINEAR");
    _filterModes.append("NEAREST");

    _wrapModes.append("REPEAT");
    _wrapModes.append("MIRRORED REPEAT");
    _wrapModes.append("CLAMP");

    ui->magFilter->addItems(_filterModes);
    ui->minFilter->addItems(_filterModes);
    ui->horizontalWrap->addItems(_wrapModes);
    ui->verticalWrap->addItems(_wrapModes);

    QObject::connect(ui->saveChanges, SIGNAL(released()),
                     textureData, SLOT(saveChanges()));
    QObject::connect(ui->loadTexture, SIGNAL(released()),
                     this, SLOT(loadTexture()));

    _textureThumbnail = new OpenGLTextureWidget(false);

    _textureThumbnail->textureToDisplayChanged(textureData->getTextureId());
    _textureThumbnail->setMinimumHeight(150);
    ui->textureLayout->addWidget(_textureThumbnail);

    _textureData = textureData;
}

LoadedTextureDataView::~LoadedTextureDataView()
{
    delete ui;
}

void LoadedTextureDataView::loadTexture()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), "", "Images \
(*.bmp *.cut *.dds *.doom *.exr *.hdr *.gif *.ico *.jp2 *.jpg *.lbm *.mdl *.mng *.pal \
*.pbm *.pcd *.pcx *.pgm *.pic *.png *.ppm *.psd *.psp *.raw *.sgi *.tga *.tif)");

    try
    {
        _textureData->loadTexture(fileName);
    }
    catch (EditorException &ex)
    {
        ex.displayErrorMessage();
    }
    _textureThumbnail->repaint();
}
