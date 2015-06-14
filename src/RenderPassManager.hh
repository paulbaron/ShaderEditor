#ifndef RENDERPASSMANAGER_H
#define RENDERPASSMANAGER_H

#include "RenderPass.hh"

class RenderPassManager
{
public:
    static RenderPassManager *getManager();

    RenderPass *getRenderPass(QString name) const;
    void setCurrent(RenderPass *current);
    void setCurrentNull();
    RenderPass *getCurrent() const;

private:
    RenderPassManager();

    static RenderPassManager *_manager;

    RenderPass *_current;
};

#endif // RENDERPASSMANAGER_H
