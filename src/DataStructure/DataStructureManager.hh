#ifndef DATASTRUCTUREMANAGER_H
#define DATASTRUCTUREMANAGER_H

#include "SInstance.hh"

#include <QList>

class DataStructureManager
{
public:
    static DataStructureManager *getManager();

    void addData(SInstance *toAdd);
    void setCurrent(SInstance *current);
    void setCurrentNull();
    SInstance *getCurrent() const;
    void removeCurrent();
    void removeData(SInstance *toRm);

    SInstance *getData(QString name);

private:
    DataStructureManager();

    static DataStructureManager *_manager;

    SContainerInstance _root;
    SInstance *_currentSelection;
};

#endif // DATASTRUCTUREMANAGER_H
