#include "RenderPass.hh"
#include "RenderPassManager.hh"

static int openGLAttachment[] =
{
    GL_DEPTH_ATTACHMENT,
    GL_DEPTH_STENCIL_ATTACHMENT,
    GL_COLOR_ATTACHMENT0,
    GL_COLOR_ATTACHMENT1,
    GL_COLOR_ATTACHMENT2,
    GL_COLOR_ATTACHMENT3,
    GL_COLOR_ATTACHMENT4,
    GL_COLOR_ATTACHMENT5,
    GL_COLOR_ATTACHMENT6
};

RenderPass::RenderPass()
{
    initializeOpenGLFunctions();
    // Shader objects
    _vertex = new QOpenGLShader(QOpenGLShader::Vertex);
    _fragment = new QOpenGLShader(QOpenGLShader::Fragment);
    _program = new QOpenGLShaderProgram;
    _codeChanged = true;
    // FBO
    glGenFramebuffers(1, &_fbo);
    for (int i = 0; i < NBR_OUTPUT; ++i)
    {
        _outputs[i] = NULL;
    }
    _width = 0;
    _height = 0;
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

SInstance *RenderPass::getInput(int inputId) const
{
    return (_root.getSon(inputId));
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
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, openGLAttachment[attachment], GL_TEXTURE_2D, texture->getTextureId(), 0);
    _outputs[attachment] = texture;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    _width = texture->getWidth();
    _height = texture->getHeight();
}

void RenderPass::unsetOutput(EOutputs attachment)
{
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, openGLAttachment[attachment], GL_TEXTURE_2D, 0, 0);
    _outputs[attachment] = NULL;
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    for (int i = 0; i < NBR_OUTPUT; ++i)
    {
        if (_outputs[i] != NULL)
            return;
    }
    _width = 0;
    _height = 0;
}

TextureData *RenderPass::getOutput(EOutputs attachment) const
{
    return (_outputs[attachment]);
}

void RenderPass::setVertexCode(QString code)
{
    _vertexCode = code;
    _codeChanged = true;
    render();
}

void RenderPass::setFragmentCode(QString code)
{
    _fragmentCode = code;
    _codeChanged = true;
    render();
}

bool RenderPass::getInputCode(SContainerInstance const *root, QString &inputCode, QString &attributeCode) const
{
    QList<SInstance*>::const_iterator it = _root.begin();
    bool vertexBufferFound = false;
    bool stopRecursion = false;

    while (it != root->end())
    {
        if ((*it)->getType() == CONTAINER_INSTANCE)
        {
            if (stopRecursion == false)
            {
                stopRecursion = getInputCode(static_cast<SContainerInstance*>(*it), inputCode, attributeCode);
            }
        }
        else
        {
            SDataInstance *inputData = static_cast<SDataInstance*>(*it);

            if (inputData->getData()->getType() == AbstractData::DATA_VERTEX_BUFFER)
            {
                // As we reach the vertex buffer, all the uniforms are supposed to be setted
                vertexBufferFound = true;
                attributeCode += inputData->getData()->getInputType() + " " + inputData->getInputName() + ";\n";
            }
            else
            {
                inputCode += inputData->getData()->getInputType() + " " + inputData->getInputName() + ";\n";
            }
        }
        ++it;
    }
    return (vertexBufferFound);
}

QString RenderPass::getOutputCode() const
{
    QString outputCode;

    for (int i = 2; i < NBR_OUTPUT; ++i)
    {
        if (_outputs[i] != NULL)
        {
            outputCode += "out vec4 Color" + QString::number(i - 1) + ";\n";
        }
    }
    return (outputCode);
}

void RenderPass::bindOutput()
{
    for (int i = 2; i < NBR_OUTPUT; ++i)
    {
        if (_outputs[i] != NULL)
        {
            QString outputName = "Color" + QString::number(i - 1);
            glBindFragDataLocation(_program->programId(), i - 2, outputName.toStdString().c_str());
        }
    }
}

void RenderPass::renderGroup(SContainerInstance const *root)
{
    QList<SInstance*>::const_iterator it = _root.begin();
    int count = 0;

    while (it != root->end())
    {
        if ((*it)->getType() == CONTAINER_INSTANCE)
        {
            renderGroup(static_cast<SContainerInstance*>(*it));
        }
        else
        {
            SDataInstance *inputData = static_cast<SDataInstance*>(*it);
            int tmpCount = inputData->setInput(_program);

            if (tmpCount != 0)
            {
                // As we reach the vertex buffer, we can start a draw
                count = tmpCount;
            }
        }
        ++it;
    }
    if (count != 0)
    {
        glDrawArrays(GL_TRIANGLES, 0, count);
    }
}

void RenderPass::render()
{
    if (_codeChanged)
    {
        QString uniformCode, attributeCode;
        QString finalVertexCode, finalFragmentCode;

        getInputCode(&_root, uniformCode, attributeCode);
        finalVertexCode = "#version 140\n" + uniformCode + "\n" + attributeCode + "\n" + _vertexCode;
        finalFragmentCode = "#version 140\n" + uniformCode + "\n" + getOutputCode() + "\n" + _fragmentCode;
        bool vertexCompile = _vertex->compileSourceCode(finalVertexCode.toStdString().c_str());
        bool fragCompile = _fragment->compileSourceCode(finalFragmentCode.toStdString().c_str());
        _program->removeAllShaders();
        bool addVertex = _program->addShader(_vertex);
        bool addFragment = _program->addShader(_fragment);
        bindOutput();
        _codeChanged = false;
    }
    glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    glClearColor(0, 1, 0, 1);
    glClearDepth(1.0f);
    glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glViewport(0, 0, _width, _height);
    _program->bind();
    renderGroup(&_root);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_DEPTH_TEST);
    emit RenderPassManager::getManager()->repaintRenderPass();
}
