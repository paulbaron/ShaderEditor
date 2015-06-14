#ifndef RENDERPASSUI_H
#define RENDERPASSUI_H

#include "RenderPass.hh"

#include <QWidget>

namespace Ui {
class RenderPassUi;
}

class RenderPassUi : public QWidget
{
    Q_OBJECT

public:
    explicit RenderPassUi(QWidget *parent = 0);
    ~RenderPassUi();

public slots:
    // Create render pass
    void createRenderPass();
    // Data changed
    void selectedDataChanged(SInstance *current);
    // Inputs slots
    void instantiate();
    void removeInstance();
    void selectedInputChanged();
    void createGroup();
    void addSon();
    void removeSon();
    // Ouput slots
    void selectedOutputChanged();
    void setOutput();
    void unsetOutput();
    // When the text is modified, change the value of the shader
    void setCurrentVertexShader();
    void setCurrentFragmentShader();

private:
    void enableOutput();

    Ui::RenderPassUi *ui;
    RenderPass *_currentPass;

    bool _addSon, _removeSon;
    bool _isAddingSon, _isRemovingSon;
};

#endif // RENDERPASSUI_H
