#include "RenderPassManager.hh"
#include "RenderPass.hh"

#include "EditorException.hh"

#include "QtOpenGLFunctions.hh"

RenderPassManager *RenderPassManager::_manager = NULL;

RenderPassManager *RenderPassManager::getManager()
{
    if (_manager == NULL)
        _manager = new RenderPassManager;
    return (_manager);
}

RenderPass *RenderPassManager::getRenderPass(int id) const
{
    if (id >= 0 && id < _renderPassList.size())
        return (_renderPassList[id]);
    return (NULL);
}

void RenderPassManager::setCurrent(int id, Ui::RenderPassUi *ui)
{
    _current = getRenderPass(id);
    if (_current != NULL)
    {
        _current->updateRenderPassUi(ui);
        _toDisplay = RenderPass::COLOR1_OUTPUT;
        RenderTextureData *toDisplay = _current->getOutput(_toDisplay);
        if (toDisplay != NULL)
        {
            emit textureToDisplayChanged(toDisplay->getTextureId());
        }
        else
        {
            emit textureToDisplayChanged(0);
        }
    }
}

void RenderPassManager::setCurrentNull()
{
    _current = NULL;
    emit textureToDisplayChanged(0);
}

RenderPassManager::RenderPassManager()
{
    setCurrentNull();
    _toDisplay = RenderPass::COLOR1_OUTPUT;
}

RenderPass *RenderPassManager::getCurrent() const
{
    return (_current);
}

void RenderPassManager::createRenderPass()
{
    _renderPassList.push_back(new RenderPass);
}

void RenderPassManager::setTextureToDisplay(RenderPass::EOutputs output)
{
    _toDisplay = output;
    if (_current && _current->getOutput(_toDisplay) != NULL)
    {
        emit textureToDisplayChanged(_current->getOutput(_toDisplay)->getTextureId());
    }
    else
    {
        emit textureToDisplayChanged(0);
    }
}

RenderPass::EOutputs RenderPassManager::getTextureToDisplay() const
{
    return (_toDisplay);
}

void RenderPassManager::removeData(AbstractData *data)
{
    for (QVector<RenderPass*>::const_iterator it = _renderPassList.begin();
         it != _renderPassList.end();
         ++it)
    {
        (*it)->removeData(data);
    }
}

int RenderPassManager::getRenderPassCount() const
{
    return (_renderPassList.size());
}

void RenderPassManager::clearAll()
{
    for (QVector<RenderPass*>::const_iterator it = _renderPassList.begin();
         it != _renderPassList.end();
         ++it)
    {
        delete *it;
    }
    _renderPassList.clear();
    _current = NULL;
    _toDisplay = RenderPass::COLOR1_OUTPUT;
}

void RenderPassManager::render()
{
    if (_current != NULL)
    {
        try
        {
            // Render all the passes
            for (QVector<RenderPass*>::const_iterator it = _renderPassList.begin();
                 *it != _current;
                 ++it)
            {
                (*it)->render();
            }
            _current->render();
            glFinish();
        }
        catch (EditorException &ex)
        {
            ex.displayErrorMessage();
        }
        // Restore the OpenGL state
        GLContext::get()->glBindFramebuffer(GL_FRAMEBUFFER, 0);
        GLContext::get()->glActiveTexture(GL_TEXTURE0);
        GLContext::get()->glDisable(GL_DEPTH_TEST);
        GLContext::get()->glDisable(GL_BLEND);
        GLContext::get()->glDisable(GL_STENCIL_TEST);
        GLContext::get()->glDisable(GL_CULL_FACE);
        emit repaintRenderPass();
    }
}

