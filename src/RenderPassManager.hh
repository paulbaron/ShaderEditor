#ifndef RENDERPASSMANAGER_H
#define RENDERPASSMANAGER_H

#include <QObject>

class RenderPass;

class RenderPassManager : public QObject
{
    Q_OBJECT

public:
    static RenderPassManager *getManager();

    RenderPass *getRenderPass(QString name) const;
    void setCurrent(RenderPass *current);
    void setCurrentNull();
    RenderPass *getCurrent() const;

signals:
    void repaintRenderPass();

private:
    RenderPassManager();

    static RenderPassManager *_manager;

    RenderPass *_current;
};

#endif // RENDERPASSMANAGER_H
