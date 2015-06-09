#ifndef DATASTRUCTUREMANAGER_H
#define DATASTRUCTUREMANAGER_H

#include "AbstractData.hh"

#include <QList>

class DataStructureManager
{
public:
    static DataStructureManager *getManager();

    void addData(AbstractData *toAdd);
    void setCurrent(QString name);
    void setCurrentNull();
    void removeCurrent();

    bool contains(QString name);

private:
    DataStructureManager();

    static DataStructureManager *_manager;

    QList<AbstractData*> _dataStructures;
    AbstractData *_currentSelection;
};

#endif // DATASTRUCTUREMANAGER_H
