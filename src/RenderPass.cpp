#include "RenderPass.hh"
#include "RenderPassManager.hh"

#include "InputChecker.hh"

#include "DataStructure/ABufferData.hh"

#include "ui_RenderPassUi.h"

#include "EditorException.hh"

#include "QtOpenGLFunctions.hh"

#include "DataStructure/DataStructureManager.hh"

#include <iostream>

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
    // Shader basic code
    QString code = "\nvoid main()\n{\n}\n";
    _vertexCode = code;
    _fragmentCode = code;
    _codeChanged = true;
    // FBO
    GLContext::get()->glGenFramebuffers(1, &_fbo);
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
    _root.clearAll();
    GLContext::get()->glDeleteFramebuffers(1, &_fbo);
}

void RenderPass::setInput(SInstance *toAdd)
{
    _root.addSon(toAdd);
}

void RenderPass::removeInput(SInstance *toRm, bool freeMemory)
{
    if (toRm->getType() == DATA_INSTANCE)
    {
        _root.removeSon(toRm);
    }
    else if (toRm->getType() == CONTAINER_INSTANCE)
    {
        if (freeMemory)
        {
            SContainerInstance *container = static_cast<SContainerInstance*>(toRm);
            QList<SInstance*>::iterator it = container->begin();

            while (it != container->end())
            {
                removeInput(*it);
                ++it;
            }
        }
        _root.removeSon(toRm);
    }
    if (freeMemory)
        delete toRm;
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

void RenderPass::removeCurrentInput(bool freeMemory)
{
    removeInput(_currentSelection, freeMemory);
    setCurrentInputNull();
}

SInstance *RenderPass::getCurrentInput() const
{
    return (_currentSelection);
}

void RenderPass::setOutput(EOutputs attachment, RenderTextureData *rt)
{
    GLContext::get()->glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    GLContext::get()->glFramebufferTexture2D(GL_FRAMEBUFFER, openGLAttachment[attachment], GL_TEXTURE_2D, rt->getTextureId(), 0);
    _outputs[attachment] = rt;
    GLContext::get()->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    _width =  rt->getWidth();
    _height = rt->getHeight();
    if (attachment == RenderPassManager::getManager()->getTextureToDisplay())
    {
        emit RenderPassManager::getManager()->textureToDisplayChanged(rt->getTextureId());
    }
}

void RenderPass::unsetOutput(EOutputs attachment)
{
    GLContext::get()->glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    GLContext::get()->glFramebufferTexture2D(GL_FRAMEBUFFER, openGLAttachment[attachment], GL_TEXTURE_2D, 0, 0);
    _outputs[attachment] = NULL;
    GLContext::get()->glBindFramebuffer(GL_FRAMEBUFFER, 0);
    if (attachment == RenderPassManager::getManager()->getTextureToDisplay())
    {
        emit RenderPassManager::getManager()->textureToDisplayChanged(0);
    }
    for (int i = 0; i < NBR_OUTPUT; ++i)
    {
        if (_outputs[i] != NULL)
            return;
    }
    _width = 0;
    _height = 0;
}

RenderTextureData *RenderPass::getOutput(EOutputs attachment) const
{
    return (_outputs[attachment]);
}

void RenderPass::setVertexCode(QString code)
{
    _vertexCode = code;
    _codeChanged = true;
}

void RenderPass::setFragmentCode(QString code)
{
    _fragmentCode = code;
    _codeChanged = true;
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
    int renderTarget = 0;
    GLenum drawBuffers[7];

    for (int i = 0; i < 7; ++i)
    {
        drawBuffers[i] = GL_NONE;
    }
    GLContext::get()->glBindFramebuffer(GL_FRAMEBUFFER, _fbo);
    for (int i = 2; i < NBR_OUTPUT; ++i)
    {
        if (_outputs[i] != NULL)
        {
            QString outputName = "Color" + QString::number(i - 1);
            drawBuffers[renderTarget] = GL_COLOR_ATTACHMENT0 + i - 2;
            GLContext::get()->glBindFragDataLocation(_shader.getProgramId(), renderTarget, outputName.toStdString().c_str());
            renderTarget += 1;
        }
    }
    GLContext::get()->glDrawBuffers(7, drawBuffers);
}

void RenderPass::renderGroup(SContainerInstance const *root)
{
    QList<SContainerInstance*> toExplore;
    bool isIndexed = false;
    int drawCallVertexCount = 0;

    for (QList<SInstance*>::const_iterator it = root->begin(); it != root->end(); ++it)
    {
        if ((*it)->getType() == CONTAINER_INSTANCE)
        {
            toExplore.push_back(static_cast<SContainerInstance*>(*it));
        }
        else
        {
            SDataInstance *inputData = static_cast<SDataInstance*>(*it);

            inputData->setInput(_shader);

            if (drawCallVertexCount == 0 &&
                inputData->getData()->getType() == AbstractData::DATA_VERTEX_BUFFER &&
                isIndexed == false)
            {
                drawCallVertexCount = static_cast<ABufferData*>(inputData->getData())->getCount();
            }
            else if (inputData->getData()->getType() == AbstractData::DATA_INDEX_BUFFER)
            {
                drawCallVertexCount = static_cast<ABufferData*>(inputData->getData())->getCount();
                isIndexed = true;
            }
        }
    }
    if (drawCallVertexCount != 0)
    {
        if (isIndexed)
        {
            GLContext::get()->glDrawElements(GL_TRIANGLES, drawCallVertexCount, GL_UNSIGNED_INT, (GLvoid*)0);
        }
        else
        {
            GLContext::get()->glDrawArrays(GL_TRIANGLES, 0, drawCallVertexCount);
        }
    }
    for (QList<SContainerInstance*>::const_iterator it = toExplore.begin(); it != toExplore.end(); ++it)
    {
        renderGroup(*it);
    }
}

void RenderPass::render()
{
    QString uniformCode, attributeCode;
    QString finalVertexCode, finalFragmentCode;
    InputChecker checker;

    // Check the inputs and get the code of the uniforms and attributes
    checker.checkInput(&_root, uniformCode, attributeCode);

    finalVertexCode = "#version 150\n" + uniformCode + "\n" + attributeCode + "\n" + _vertexCode;
    finalFragmentCode = "#version 150\n" + uniformCode + "\n" + getOutputCode() + "\n" + _fragmentCode;
    try
    {
        _shader.load(finalVertexCode, GLSLShader::VERTEX_SHADER);
        _shader.load(finalFragmentCode, GLSLShader::FRAGMENT_SHADER);
        _shader.build();
        _shader.bind();
        bindOutput();
        GLContext::get()->glViewport(0, 0, _width, _height);
        _state.setOpenGLState();
        renderGroup(&_root);
    }
    catch (EditorException &ex)
    {
        ex.displayErrorMessage();
    }
}

void RenderPass::updateOpenGLState(Ui::RenderPassUi *ui)
{
    _state.updateOpenGLState(ui);
}

void RenderPass::updateRenderPassUi(Ui::RenderPassUi *ui)
{
    ui->vertexCodeEdit->setPlainText(_vertexCode);
    ui->fragmentCodeEdit->setPlainText(_fragmentCode);
    ui->treeWidget->clear();

    for (QList<SInstance*>::const_iterator it = _root.begin(); it != _root.end(); ++it)
    {
        ui->treeWidget->addTopLevelItem((*it)->getTreeItem());
    }
    ui->inputName->setEnabled(false);
    ui->addSon->setEnabled(false);
    ui->removeSon->setEnabled(false);
    ui->tableWidget->clearContents();
    for (int i = 0; i < NBR_OUTPUT; ++i)
    {
        if (_outputs[i] != NULL)
        {
            QTableWidgetItem *item = new QTableWidgetItem(getOutput((EOutputs)i)->getName());
            ui->tableWidget->setItem(i, 0, item);
        }
    }
    ui->setOutput->setEnabled(false);
    ui->unsetOutput->setEnabled(false);
    _state.updateUiState(ui);
}

void RenderPass::removeData(AbstractData *data)
{
    _root.removeSonsData(data);
}
