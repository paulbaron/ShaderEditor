#ifndef RENDERPASS_H
#define RENDERPASS_H

#include <QVector>
#include <QOpenGLShaderProgram>
#include <QOpenGLShader>
#include <QOpenGLFunctions>

#include "DataStructure/SInstance.hh"
#include "DataStructure/TextureData.hh"

class RenderPass : public QOpenGLFunctions
{
public:
    enum EOutputs
    {
        DEPTH_OUTPUT,
        DEPTH_STENCIL_OUTPUT,
        COLOR1_OUTPUT,
        COLOR2_OUTPUT,
        COLOR3_OUTPUT,
        COLOR4_OUTPUT,
        COLOR5_OUTPUT,
        COLOR6_OUTPUT,
        COLOR7_OUTPUT,
        NBR_OUTPUT
    };

    RenderPass();
    ~RenderPass();

    QOpenGLShaderProgram *getProgram() const { return (_program); }

    // Input
    void setInput(SInstance *toAdd);
    bool removeInput(SInstance *toRm);
    SInstance *getInput(QString name) const;
    // input selection
    void setCurrentInput(SInstance *current);
    void setCurrentInputNull();
    void removeCurrentInput();
    SInstance *getCurrentInput() const;
    // Output
    void setOutput(EOutputs attachment, TextureData *texture);
    void unsetOutput(EOutputs attachment);
    TextureData *getOutput(EOutputs attachment) const;
    // Shaders
    void setVertexCode(QString code);
    void setFragmentCode(QString code);
    // Render functions
    void renderGroup(SContainerInstance *root) const;
    void render() const;

private:
    // Shader code
    QString _vertexCode;
    QString _fragmentCode;
    // Shader objects
    QOpenGLShader *_vertex;
    QOpenGLShader *_fragment;
    QOpenGLShaderProgram *_program;
    // FBO
    GLuint _fbo;
    TextureData *_outputs[NBR_OUTPUT];
   // Inputs
    SContainerInstance _root;
    SInstance *_currentSelection;
    // Links
    QList<RenderPass*> _previous;
    QList<RenderPass*> _next;
};

#endif // RENDERPASS_H
