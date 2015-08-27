#include "LoadedTextureData.hh"

#include "DataStructureManager.hh"
#include "View/LoadedTextureDataView.hh"
#include "ui_LoadedTextureDataView.h"

#include "EditorException.hh"

#include "QtOpenGLFunctions.hh"

#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

BOOST_CLASS_EXPORT_IMPLEMENT(LoadedTextureData)

bool LoadedTextureData::_devilLoaded = false;

LoadedTextureData::LoadedTextureData() :
    ATextureData("LoadedTexture_")
{
    if (_devilLoaded == false)
    {
        ilInit();
        iluInit();
        _devilLoaded = true;
    }
    _type = DATA_LOADED_TEXTURE;
    _view = new LoadedTextureDataView(this);
    updateUi();
    updateOpenGLParameters();
}

LoadedTextureData::~LoadedTextureData()
{

}

void LoadedTextureData::loadTexture(QString filePath)
{
    ILuint imageID;
    ILenum error;

    ilGenImages(1, &imageID);
    ilBindImage(imageID);
    if (ilLoadImage(filePath.toStdString().c_str()) == false)
    {
        error = ilGetError();
        QString title = "Could not load the image.";
        QString details = "The image file " + filePath +
                "has not been loaded.\nIL error: '" +
                iluErrorString(error) + "'.";


        ilBindImage(0);
        ilDeleteImages(1, &imageID);
        throw EditorException(title, details);
    }
    ILinfo ImageInfo;
    iluGetImageInfo(&ImageInfo);
    if (ImageInfo.Origin == IL_ORIGIN_UPPER_LEFT)
    {
        iluFlipImage();
    }
    GLvoid *pixelData = ilGetData();
    _width  = ilGetInteger(IL_IMAGE_WIDTH);
    _height = ilGetInteger(IL_IMAGE_HEIGHT);
    _format = ilGetInteger(IL_IMAGE_FORMAT);
    GLenum type = (GLenum)ilGetInteger(IL_IMAGE_TYPE);
    GLContext::get()->glBindTexture(GL_TEXTURE_2D, _id);
    GLContext::get()->glPixelStorei(GL_UNPACK_SWAP_BYTES, GL_FALSE);
    GLContext::get()->glPixelStorei(GL_UNPACK_ROW_LENGTH, 0);
    GLContext::get()->glPixelStorei(GL_UNPACK_SKIP_PIXELS, 0);
    GLContext::get()->glPixelStorei(GL_UNPACK_SKIP_ROWS, 0);
    GLContext::get()->glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    GLContext::get()->glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, _format, type, pixelData);
    ilBindImage(0);
    ilDeleteImages(1, &imageID);
    updateOpenGLParameters();
    _texturePath = filePath;
}

void LoadedTextureData::saveChanges()
{
    LoadedTextureDataView *texView = static_cast<LoadedTextureDataView*>(_view);
    Ui::LoadedTextureDataView *ui = texView->getUi();

    _magFilter = getFilterModeFromIndex(ui->magFilter->currentIndex());
    _minFilter = getFilterModeFromIndex(ui->minFilter->currentIndex());
    _verticalWrapMode = getWrapModeFromIndex(ui->verticalWrap->currentIndex());
    _horizontalWrapMode = getWrapModeFromIndex(ui->horizontalWrap->currentIndex());
    updateOpenGLParameters();
    emit DataStructureManager::getManager()->textureChangedType();
}

void LoadedTextureData::updateUi()
{
    LoadedTextureDataView *texView = static_cast<LoadedTextureDataView*>(_view);
    Ui::LoadedTextureDataView *ui = texView->getUi();
    ui->magFilter->setCurrentIndex(getIndexFromFilterMode(_magFilter));
    ui->minFilter->setCurrentIndex(getIndexFromFilterMode(_minFilter));
    ui->verticalWrap->setCurrentIndex(getIndexFromWrapMode(_verticalWrapMode));
    ui->horizontalWrap->setCurrentIndex(getIndexFromWrapMode(_horizontalWrapMode));
}

void LoadedTextureData::updateOpenGLParameters()
{
    GLContext::get()->glBindTexture(GL_TEXTURE_2D, _id);
    GLContext::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    GLContext::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
    GLContext::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _horizontalWrapMode);
    GLContext::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _verticalWrapMode);
}
