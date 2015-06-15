#include "RenderPassManager.hh"
#include "RenderPass.hh"

RenderPassManager *RenderPassManager::_manager = NULL;

RenderPassManager *RenderPassManager::getManager()
{
    if (_manager == NULL)
        _manager = new RenderPassManager;
    return (_manager);
}

RenderPass *RenderPassManager::getRenderPass(QString name) const
{
    return (NULL);
}

void RenderPassManager::setCurrent(RenderPass *current)
{
    _current = current;
}

void RenderPassManager::setCurrentNull()
{
    _current = NULL;
}

RenderPassManager::RenderPassManager()
{
    _current = new RenderPass;
}

RenderPass *RenderPassManager::getCurrent() const
{
    return (_current);
}

