#ifndef CONTAINERDATA_H
#define CONTAINERDATA_H

#include <QList>

#include "AbstractData.hh"

class ContainerData : public AbstractData
{
public:
    ContainerData();
    ~ContainerData();

    bool addSon(AbstractData *toAdd);
    void removeSon(AbstractData *toRm);

public slots:
    void saveChanges() { }

private:
    QList<AbstractData*> _sons;
};

#endif // CONTAINERDATA_H
