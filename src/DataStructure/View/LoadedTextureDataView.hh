#ifndef LOADEDTEXTUREDATAVIEW_HH
#define LOADEDTEXTUREDATAVIEW_HH

#include <QWidget>

#include "../LoadedTextureData.hh"
#include "OpenGLTextureWidget.hh"

namespace Ui {
class LoadedTextureDataView;
}

class LoadedTextureDataView : public QWidget
{
    Q_OBJECT

public:
    explicit LoadedTextureDataView(LoadedTextureData *textureData, QWidget *parent = 0);
    ~LoadedTextureDataView();

    Ui::LoadedTextureDataView *getUi() const { return (ui); }

public slots:
    void loadTexture();

private:
    Ui::LoadedTextureDataView *ui;

    QStringList _filterModes;
    QStringList _wrapModes;

    OpenGLTextureWidget *_textureThumbnail;
    LoadedTextureData *_textureData;
};

#endif // LOADEDTEXTUREDATAVIEW_HH
