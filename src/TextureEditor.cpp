#include "TextureEditor.hh"
#include "ui_TextureEditor.h"

#include "OpenGLTextureManager.hh"

#include <QErrorMessage>
#include <assert.h>

TextureEditor::TextureEditor(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TextureEditor)
{
    ui->setupUi(this);

    QObject::connect(ui->createTexture, SIGNAL(released()),
                     this, SLOT(textureAdded()));
    QObject::connect(ui->listWidget, SIGNAL(itemSelectionChanged()),
                     this, SLOT(textureSelected()));
    QObject::connect(ui->deleteTexture, SIGNAL(released()),
                     this, SLOT(textureRemoved()));
    QObject::connect(ui->saveChanges, SIGNAL(released()),
                     this, SLOT(saveChanges()));

    _pixelFormats.append("GL_DEPTH_COMPONENT16");
    _pixelFormats.append("GL_DEPTH_COMPONENT24");
    _pixelFormats.append("GL_DEPTH_COMPONENT32");
    _pixelFormats.append("GL_DEPTH24_STENCIL8");
    _pixelFormats.append("GL_R8");
    _pixelFormats.append("GL_R16UI");
    _pixelFormats.append("GL_R16F");
    _pixelFormats.append("GL_R32F");
    _pixelFormats.append("GL_RG8");
    _pixelFormats.append("GL_RG16UI");
    _pixelFormats.append("GL_RG16F");
    _pixelFormats.append("GL_RG32F");
    _pixelFormats.append("GL_RGB8");
    _pixelFormats.append("GL_RGB16UI");
    _pixelFormats.append("GL_RGB16F");
    _pixelFormats.append("GL_RGB32F");
    _pixelFormats.append("GL_RGBA8");
    _pixelFormats.append("GL_RGBA16UI");
    _pixelFormats.append("GL_RGBA16F");
    _pixelFormats.append("GL_RGBA32F");

    _filterModes.append("LINEAR");
    _filterModes.append("NEAREST");

    _wrapModes.append("REPEAT");
    _wrapModes.append("MIRRORED REPEAT");
    _wrapModes.append("CLAMP");

    ui->texturePixelFormat->addItems(_pixelFormats);
    ui->magFilter->addItems(_filterModes);
    ui->minFilter->addItems(_filterModes);
    ui->horizontalWrap->addItems(_wrapModes);
    ui->verticalWrap->addItems(_wrapModes);
}

TextureEditor::~TextureEditor()
{
    delete ui;
}

void TextureEditor::textureAdded()
{
    static int currentTexture = 0;
    OpenGLTextureManager::STextureData data;
    bool hasBeenInserted;

    do
    {
        data.name = "Texture " + QString::number(currentTexture++);
        hasBeenInserted = OpenGLTextureManager::getManager()->getTextureData(data.name) == NULL;
        if (hasBeenInserted)
        {
            OpenGLTextureManager::getManager()->setTextureData(data);
        }
    } while (hasBeenInserted == false);

    ui->listWidget->addItem(data.name);
}

void TextureEditor::textureRemoved()
{
    QString name = ui->listWidget->currentItem()->text();

    OpenGLTextureManager::getManager()->removeTexture(name);

    delete ui->listWidget->takeItem(ui->listWidget->currentRow());

    if (ui->listWidget->currentItem() == NULL)
        enableUi(false);
}

void TextureEditor::textureSelected()
{
    if (ui->listWidget->currentItem() == NULL)
        return;
    QString name = ui->listWidget->currentItem()->text();
    OpenGLTextureManager::STextureData const *data = OpenGLTextureManager::getManager()->getTextureData(name);
    assert(data != NULL);
    ui->textureName->setText(name);
    ui->Width->setValue(data->width);
    ui->Height->setValue(data->height);
    ui->texturePixelFormat->setCurrentIndex(getIndexFromPixelFormat(data->format));
    ui->horizontalWrap->setCurrentIndex(getIndexFromWrapMode(data->horizontalWrapMode));
    ui->verticalWrap->setCurrentIndex(getIndexFromWrapMode(data->verticalWrapMode));
    ui->minFilter->setCurrentIndex(getIndexFromFilterMode(data->minFilter));
    ui->magFilter->setCurrentIndex(getIndexFromFilterMode(data->magFilter));

    enableUi(true);
}

void TextureEditor::saveChanges()
{
    QString name = ui->listWidget->currentItem()->text();

    OpenGLTextureManager::STextureData newData;
    OpenGLTextureManager::STextureData const *oldData = OpenGLTextureManager::getManager()->getTextureData(name);
    assert(oldData != NULL);

    newData.id = oldData->id;
    newData.format = getPixelFormatFromIndex(ui->texturePixelFormat->currentIndex());
    newData.horizontalWrapMode = getWrapModeFromIndex(ui->horizontalWrap->currentIndex());
    newData.verticalWrapMode = getWrapModeFromIndex(ui->verticalWrap->currentIndex());
    newData.minFilter = getFilterModeFromIndex(ui->minFilter->currentIndex());
    newData.magFilter = getFilterModeFromIndex(ui->magFilter->currentIndex());
    newData.width = ui->Width->value();
    newData.height = ui->Height->value();
    newData.name = ui->textureName->text();

    // If the name has changed and a similar name already exist
    if (newData.name != oldData->name &&
        OpenGLTextureManager::getManager()->getTextureData(newData.name) != NULL)
    {
        QErrorMessage msg;

        msg.exec();
    }
    else
    {
        OpenGLTextureManager::getManager()->setTextureData(newData);
        ui->listWidget->currentItem()->setText(newData.name);
    }
}

GLenum TextureEditor::getPixelFormatFromIndex(int idx) const
{
    return (OpenGLTextureManager::getManager()->getFormatFromIndex(idx));
}

int TextureEditor::getIndexFromPixelFormat(GLenum format) const
{
    return (OpenGLTextureManager::getManager()->getIndexFromFormat(format));
}

GLenum TextureEditor::getWrapModeFromIndex(int idx) const
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

int TextureEditor::getIndexFromWrapMode(GLenum wrap) const
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

GLenum TextureEditor::getFilterModeFromIndex(int idx) const
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

int TextureEditor::getIndexFromFilterMode(GLenum filter) const
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

void TextureEditor::enableUi(bool enabled)
{
    ui->textureName->setEnabled(enabled);
    ui->Width->setEnabled(enabled);
    ui->Height->setEnabled(enabled);
    ui->texturePixelFormat->setEnabled(enabled);
    ui->horizontalWrap->setEnabled(enabled);
    ui->verticalWrap->setEnabled(enabled);
    ui->minFilter->setEnabled(enabled);
    ui->magFilter->setEnabled(enabled);

    ui->deleteTexture->setEnabled(enabled);
    ui->saveChanges->setEnabled(enabled);

    ui->label->setEnabled(enabled);
    ui->label_2->setEnabled(enabled);
    ui->label_3->setEnabled(enabled);
    ui->label_4->setEnabled(enabled);
    ui->label_5->setEnabled(enabled);
    ui->label_6->setEnabled(enabled);
    ui->label_7->setEnabled(enabled);
}
