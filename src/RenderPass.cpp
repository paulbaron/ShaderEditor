#include "RenderPass.hh"

RenderPass::RenderPass()
{
    initializeOpenGLFunctions();
    // Shader code
    _vertexCode;
    _fragmentCode;
    // Shader objects
    _vertex = NULL;
    _fragment = NULL;
    _program = NULL;
    // FBO
    glGenFramebuffers(1, &_fbo);
    for (int i = 0; i < NBR_OUTPUT; ++i)
    {
        _outputs[i] = NULL;
    }
   // Inputs
    _currentSelection = NULL;
}

RenderPass::~RenderPass()
{
    delete _vertex;
    delete _fragment;
    delete _program;
    glDeleteFramebuffers(1, &_fbo);
}

void RenderPass::setInput(SInstance *toAdd)
{
    _root.addSon(toAdd);
}

bool RenderPass::removeInput(SInstance *toRm)
{
    return (_root.removeSon(toRm));
}

SInstance *RenderPass::getInput(QString name) const
{
    return (_root.getSon(name));
}

void RenderPass::setCurrentInput(SInstance *current)
{
    _currentSelection = current;
}

void RenderPass::setCurrentInputNull()
{
    _currentSelection = NULL;
}

void RenderPass::removeCurrentInput()
{
    removeInput(_currentSelection);
    setCurrentInputNull();
}

SInstance *RenderPass::getCurrentInput() const
{
    return (_currentSelection);
}

void RenderPass::setOutput(EOutputs attachment, TextureData *texture)
{
    _outputs[attachment] = texture;
}

void RenderPass::unsetOutput(EOutputs attachment)
{
    _outputs[attachment] = NULL;
}

TextureData *RenderPass::getOutput(EOutputs attachment) const
{
    return (_outputs[attachment]);
}

void RenderPass::setVertexCode(QString code)
{
    _vertexCode = code;
}

void RenderPass::setFragmentCode(QString code)
{
    _fragmentCode = code;
}

void RenderPass::render() const
{
    // OpenGL rendering HERE
}
