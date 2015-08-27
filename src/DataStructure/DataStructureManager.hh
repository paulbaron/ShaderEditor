#ifndef DATASTRUCTUREMANAGER_H
#define DATASTRUCTUREMANAGER_H

#include "SInstance.hh"
#include "IndexBufferData.hh"
#include "Vec2BufferData.hh"
#include "Vec3BufferData.hh"
#include "LoadedTextureData.hh"
#include "RenderTextureData.hh"
#include "Mat4Data.hh"

#include <QMap>
#include <QObject>

#include <boost/serialization/map.hpp>

class AbstractData;

class DataStructureManager : public QObject
{
    Q_OBJECT

public:
    static DataStructureManager *getManager();

    SDataInstance *addData(AbstractData *toAdd);
    SContainerInstance *addContainer();
    void setCurrent(int id);
    void setCurrentNull();
    SInstance *getCurrent() const;
    void removeCurrent(bool freeMemory = true);
    void removeInstance(SInstance *toRm, bool freeMemory = false);

    SContainerInstance const &getRoot() const;
    SInstance *getInstance(int id);
    SInstance *getInstance(QString name);

    AbstractData *getData(int id);

    void clearAll();

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        std::map<int, AbstractData*> dataCollection(_dataCollection.toStdMap());
        ar & boost::serialization::make_nvp("dataCollection", dataCollection)
            & boost::serialization::make_nvp("dataTree", _root);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        clearAll();
        std::map<int, AbstractData*> dataCollection;
        ar & boost::serialization::make_nvp("dataCollection", dataCollection)
            & boost::serialization::make_nvp("dataTree", _root);
        _dataCollection = QMap<int, AbstractData*>(dataCollection);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

signals:
    void currentSelectionChanged(SInstance *current);
    void textureChangedType();

private:
    DataStructureManager();

    static DataStructureManager *_manager;

    QMap<int, AbstractData*> _dataCollection;

    SContainerInstance _root;
    SInstance *_currentSelection;
};

#endif // DATASTRUCTUREMANAGER_H
