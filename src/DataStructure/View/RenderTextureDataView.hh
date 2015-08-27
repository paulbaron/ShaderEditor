#ifndef TEXTUREEDITOR_HH
#define TEXTUREEDITOR_HH

#include <QWidget>
#include <QOpenGLContext>
#include <QListWidgetItem>

#include "../AbstractData.hh"

namespace Ui {
class RenderTextureDataView;
}

class RenderTextureDataView : public QWidget
{
    Q_OBJECT

public:
    explicit RenderTextureDataView(AbstractData *data, QWidget *parent = 0);
    ~RenderTextureDataView();

    Ui::RenderTextureDataView *getUi() const { return (ui); }

private:
    Ui::RenderTextureDataView *ui;

    QStringList _pixelFormats;
    QStringList _filterModes;
    QStringList _wrapModes;
};

#endif // TEXTUREEDITOR_HH
