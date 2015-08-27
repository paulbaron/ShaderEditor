#ifndef RENDERPASSUI_H
#define RENDERPASSUI_H

#include "RenderPass.hh"
#include "DataStructure/View/GLSLHighlighter.hh"

#include <QWidget>

#include <QTreeWidgetItem>

namespace Ui {
class RenderPassUi;
}

class RenderPassUi : public QWidget
{
    Q_OBJECT

public:
    explicit RenderPassUi(QWidget *parent = 0);
    ~RenderPassUi();

    Ui::RenderPassUi *getUi() const { return (ui); }

public slots:
    // Data changed
    void selectedDataChanged(SInstance *current);
    // OpenGL State changed
    void updateOpenGLState();
    // Inputs slots
    void instantiate();
    void removeInstance();
    void selectedInputChanged();
    void createGroup();
    void addSon();
    void removeSon();
    void inputNameChanged();
    // Ouput slots
    void selectedOutputChanged();
    void setOutput();
    void unsetOutput();
    // When the text is modified, change the value of the shader
    void setCurrentVertexShader();
    void setCurrentFragmentShader();
    // Check if the set output button should be activated
    void checkEnableOutput();
    // Add snippet
    void addSnippet();

private:
    Ui::RenderPassUi *ui;

    QTreeWidgetItem *_currentSelection;
    bool _addSon, _removeSon;
    bool _isAddingSon, _isRemovingSon;
    GLSLHighlighter *_vertexHighlighter;
    GLSLHighlighter *_fragmentHighlighter;
};

#endif // RENDERPASSUI_H
