#ifndef TEXTUREEDITOR_HH
#define TEXTUREEDITOR_HH

#include <QWidget>
#include <QOpenGLContext>
#include <QListWidgetItem>

namespace Ui {
class TextureDataView;
}

class TextureDataView : public QWidget
{
    Q_OBJECT

public:
    explicit TextureDataView(QWidget *parent = 0);
    ~TextureDataView();

    Ui::TextureDataView *getUi() const { return (ui); }

private:
    Ui::TextureDataView *ui;

    QStringList _pixelFormats;
    QStringList _filterModes;
    QStringList _wrapModes;
};

#endif // TEXTUREEDITOR_HH