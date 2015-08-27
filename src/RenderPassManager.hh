#ifndef RENDERPASSMANAGER_H
#define RENDERPASSMANAGER_H

#include <QObject>
#include <QOpenGLContext>
#include <QVector>

#include "RenderPass.hh"

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/vector.hpp>

namespace Ui {
class RenderPassUi;
}

class RenderPassManager : public QObject
{
    Q_OBJECT

public:
    static RenderPassManager *getManager();

    RenderPass *getRenderPass(int id) const;
    void setCurrent(int id, Ui::RenderPassUi *ui);
    void setCurrentNull();
    RenderPass *getCurrent() const;
    void createRenderPass();

    void setTextureToDisplay(RenderPass::EOutputs output);
    RenderPass::EOutputs getTextureToDisplay() const;

    void removeData(AbstractData *data);

    int getRenderPassCount() const;
    void clearAll();

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        std::vector<RenderPass*> renderPassList(_renderPassList.toStdVector());
        ar & boost::serialization::make_nvp("renderPassList", renderPassList);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        clearAll();
        std::vector<RenderPass*> renderPassList;
        ar & boost::serialization::make_nvp("renderPassList", renderPassList);
        _renderPassList = QVector<RenderPass*>::fromStdVector(renderPassList);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public slots:
    void render();

signals:
    void repaintRenderPass();
    void textureToDisplayChanged(GLuint texture);

private:
    RenderPassManager();

    static RenderPassManager *_manager;

    QVector<RenderPass*> _renderPassList;
    RenderPass *_current;
    RenderPass::EOutputs _toDisplay;
};

#endif // RENDERPASSMANAGER_H
