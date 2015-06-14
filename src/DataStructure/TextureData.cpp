#include "TextureData.hh"
#include "View/TextureDataView.hh"
#include "ui_TextureDataView.h"

#include "DataStructureManager.hh"

#include <assert.h>

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
    {GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE},
    {GL_RGBA16UI, GL_RGB, GL_UNSIGNED_INT},
    {GL_RGBA16F, GL_RGB, GL_FLOAT},
    {GL_RGBA32F, GL_RGB, GL_FLOAT},
    {(GLenum)-1, (GLenum)-1, (GLenum)-1}
};

TextureData::TextureData()
{
    _type = DATA_TEXTURE;
    _view = new TextureDataView(this);
    // Set the default texture parameters
    glGenTextures(1, &_id);
    _format = GL_RGBA8;
    _magFilter = GL_LINEAR;
    _minFilter = GL_LINEAR;
    _verticalWrapMode = GL_CLAMP;
    _horizontalWrapMode = GL_CLAMP;
    _width = 800;
    _height = 600;
    updateUi();
    updateOpenGLParameters();
}

TextureData::~TextureData()
{
    glDeleteTextures(1, &_id);
}

GLenum TextureData::getInternalFormat() const
{
    return (_format);
}

void TextureData::saveChanges()
{
    TextureDataView *texView = static_cast<TextureDataView*>(_view);
    Ui::TextureDataView *ui = texView->getUi();

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

GLenum TextureData::getPixelFormatFromIndex(int idx) const
{
    assert(idx < sizeof(textureFormatTable) / sizeof(textureFormatTable[0]) - 1);
    return (textureFormatTable[idx][0]);
}

int TextureData::getIndexFromPixelFormat(GLenum format) const
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

GLenum TextureData::getWrapModeFromIndex(int idx) const
{
    if (idx == 0)
        return (GL_REPEAT);
    else if (idx == 1)
        return (GL_MIRRORED_REPEAT);
    else if (idx == 2)
        return (GL_CLAMP);
    else
    {
        assert(!"Unknown filter index");
        return ((GLenum)-1);
    }
}

int TextureData::getIndexFromWrapMode(GLenum wrap) const
{
    if (wrap == GL_REPEAT)
        return (0);
    else if (wrap == GL_MIRRORED_REPEAT)
        return (1);
    else if (wrap == GL_CLAMP)
        return (2);
    else
    {
        assert(!"Unknown filter");
        return (-1);
    }
}

GLenum TextureData::getFilterModeFromIndex(int idx) const
{
    if (idx == 0)
        return (GL_LINEAR);
    else if (idx == 1)
        return (GL_NEAREST);
    else
    {
        assert(!"Unknown wrap mode index");
        return ((GLenum)-1);
    }
}

int TextureData::getIndexFromFilterMode(GLenum filter) const
{
    if (filter == GL_LINEAR)
        return (0);
    else if (filter == GL_NEAREST)
        return (1);
    else
    {
        assert(!"Unknown wrap mode");
        return (-1);
    }
}

void TextureData::getFormatInfo(GLenum internalFormat, GLenum &format, GLenum &type)
{
    int idx = getIndexFromPixelFormat(internalFormat);
    format = textureFormatTable[idx][1];
    type = textureFormatTable[idx][2];
}

void TextureData::updateUi()
{
    TextureDataView *texView = static_cast<TextureDataView*>(_view);
    Ui::TextureDataView *ui = texView->getUi();
    ui->Width->setValue(_width);
    ui->Height->setValue(_height);
    ui->magFilter->setCurrentIndex(getIndexFromFilterMode(_magFilter));
    ui->minFilter->setCurrentIndex(getIndexFromFilterMode(_minFilter));
    ui->verticalWrap->setCurrentIndex(getIndexFromWrapMode(_verticalWrapMode));
    ui->horizontalWrap->setCurrentIndex(getIndexFromWrapMode(_horizontalWrapMode));
    ui->texturePixelFormat->setCurrentIndex(getIndexFromPixelFormat(_format));
}

void TextureData::updateOpenGLParameters()
{
    GLenum format, type;

    getFormatInfo(_format, format, type);
    glBindTexture(GL_TEXTURE_2D, _id);
    glTexImage2D(GL_TEXTURE_2D, 0, _format, _width, _height, 0, format, type, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, _minFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, _magFilter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, _horizontalWrapMode);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, _verticalWrapMode);
}
