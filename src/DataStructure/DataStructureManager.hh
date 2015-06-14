#ifndef DATASTRUCTUREMANAGER_H
#define DATASTRUCTUREMANAGER_H

#include "SInstance.hh"

#include <QList>
#include <QObject>

class DataStructureManager : public QObject
{
    Q_OBJECT

public:
    static DataStructureManager *getManager();

    void addData(SInstance *toAdd);
    void setCurrent(SInstance *current);
    void setCurrentNull();
    SInstance *getCurrent() const;
    void removeCurrent();
    bool removeData(SInstance *toRm);

    SInstance *getData(QString name);

signals:
    void currentSelectionChanged(SInstance *current);
    void textureChangedType();

private:
    DataStructureManager();

    static DataStructureManager *_manager;

    SContainerInstance _root;
    SInstance *_currentSelection;
};

#endif // DATASTRUCTUREMANAGER_H
