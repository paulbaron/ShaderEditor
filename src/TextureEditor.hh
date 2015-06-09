#ifndef TEXTUREEDITOR_HH
#define TEXTUREEDITOR_HH

#include <QWidget>
#include <QOpenGLContext>
#include <QListWidgetItem>

namespace Ui {
class TextureEditor;
}

class TextureEditor : public QWidget
{
    Q_OBJECT

public:
    explicit TextureEditor(QWidget *parent = 0);
    ~TextureEditor();

public slots:
    void textureAdded();
    void textureRemoved();
    void textureSelected();
    void saveChanges();

private:
    Ui::TextureEditor *ui;

    GLenum getPixelFormatFromIndex(int idx) const;
    int getIndexFromPixelFormat(GLenum format) const;

    GLenum getWrapModeFromIndex(int idx) const;
    int getIndexFromWrapMode(GLenum format) const;

    GLenum getFilterModeFromIndex(int idx) const;
    int getIndexFromFilterMode(GLenum format) const;

    void enableUi(bool enabled);

    QStringList _pixelFormats;
    QStringList _filterModes;
    QStringList _wrapModes;
};

#endif // TEXTUREEDITOR_HH
