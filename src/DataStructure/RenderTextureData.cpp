#include "RenderTextureData.hh"
#include "View/RenderTextureDataView.hh"
#include "ui_RenderTextureDataView.h"

#include "DataStructureManager.hh"

#include "QtOpenGLFunctions.hh"

#include <assert.h>

BOOST_CLASS_EXPORT_IMPLEMENT(RenderTextureData)

// Useful table to call glTexImage
static GLenum textureFormatTable[][3] =
{
    {GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE},
    {GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE},
    {GL_DEPTH_COMPONENT32, GL_DEPTH_COMPONENT, GL_UNSIGNED_INT},
    {GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_INT},
    {GL_R8, GL_RED, GL_UNSIGNED_BYTE},
    {GL_R16UI, GL_RED, GL_UNSIGNED_INT},
    {GL_R16F, GL_RED, GL_FLOAT},
    {GL_R32F, GL_RED, GL_FLOAT},
    {GL_RG8, GL_RG, GL_UNSIGNED_BYTE},
    {GL_RG16UI, GL_RG, GL_UNSIGNED_INT},
    {GL_RG16F, GL_RG, GL_FLOAT},
    {GL_RG32F, GL_RG, GL_FLOAT},
    {GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE},
    {GL_RGB16UI, GL_RGB, GL_UNSIGNED_INT},
    {GL_RGB16F, GL_RGB, GL_FLOAT},
    {GL_RGB32F, GL_RGB, GL_FLOAT},
    {GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE},
    {GL_RGBA16UI, GL_RGBA, GL_UNSIGNED_INT},
    {GL_RGBA16F, GL_RGBA, GL_FLOAT},
    {GL_RGBA32F, GL_RGBA, GL_FLOAT},
    {(GLenum)-1, (GLenum)-1, (GLenum)-1}
};

RenderTextureData::RenderTextureData() :
    ATextureData("RenderTexture_")
{
    _type = DATA_RENDER_TEXTURE;
    _view = new RenderTextureDataView(this);
    _width = 1280;
    _height = 720;
    updateUi();
    updateOpenGLParameters();
}

RenderTextureData::~RenderTextureData()
{
}


void RenderTextureData::saveChanges()
{
    RenderTextureDataView *texView = static_cast<RenderTextureDataView*>(_view);
    Ui::RenderTextureDataView *ui = texView->getUi();

    _format = getPixelFormatFromIndex(ui->texturePixelFormat->currentIndex());
    _magFilter = getFilterModeFromIndex(ui->magFilter->currentIndex());
    _minFilter = getFilterModeFromIndex(ui->minFilter->currentIndex());
    _verticalWrapMode = getWrapModeFromIndex(ui->verticalWrap->currentIndex());
    _horizontalWrapMode = getWrapModeFromIndex(ui->horizontalWrap->currentIndex());
    _width = ui->Width->value();
    _height = ui->Height->value();
    updateOpenGLParameters();
    emit DataStructureManager::getManager()->textureChangedType();
}

GLenum RenderTextureData::getPixelFormatFromIndex(int idx) const
{
    assert(idx < sizeof(textureFormatTable) / sizeof(textureFormatTable[0]) - 1);
    return (textureFormatTable[idx][0]);
}

int RenderTextureData::getIndexFromPixelFormat(GLenum format) const
{
    int idx = 0;

    while (textureFormatTable[idx][0] != (GLenum)-1 &&
           textureFormatTable[idx][0] != format)
    {
        ++idx;
    }
    assert(textureFormatTable[idx][0] != (GLenum)-1);
    return (idx);
}

void RenderTextureData::updateUi()
{
    RenderTextureDataView *texView = static_cast<RenderTextureDataView*>(_view);
    Ui::RenderTextureDataView *ui = texView->getUi();
    ui->Width->setValue(_width);
    ui->Height->setValue(_height);
    ui->magFilter->setCurrentIndex(getIndexFromFilterMode(_magFilter));
    ui->minFilter->setCurrentIndex(getIndexFromFilterMode(_minFilter));
    ui->verticalWrap->setCurrentIndex(getIndexFromWrapMode(_verticalWrapMode));
    ui->horizontalWrap->setCurrentIndex(getIndexFromWrapMode(_horizontalWrapMode));
    ui->texturePixelFormat->setCurrentIndex(getIndexFromPixelFormat(_format));
}

void RenderTextureData::getFormatInfo(GLenum internalFormat, GLenum &format, GLenum &type)
{
    int idx = getIndexFromPixelFormat(internalFormat);
    format = textureFormatTable[idx][1];
    type = textureFormatTable[idx][2];
}

void RenderTextureData::updateOpenGLParameters()
{
    GLenum format, type;

    getFormatInfo(_format, format, type);
    GLContext::get()->glBindTexture(GL_TEXTURE_2D, _id);
    GLContext::get()->glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, format, type, NULL);
    GLContext::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    GLContext::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
    GLContext::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _horizontalWrapMode);
    GLContext::get()->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _verticalWrapMode);
}
