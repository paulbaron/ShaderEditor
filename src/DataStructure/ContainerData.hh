#ifndef CONTAINERDATA_H
#define CONTAINERDATA_H

#include <QList>

#include "AbstractData.hh"

class ContainerData : public AbstractData
{
public:
    ContainerData();
    ~ContainerData();

    void addSon(AbstractData *toAdd);
    bool removeSon(AbstractData *toRm);

    AbstractData *getData(QString name) const;

public slots:
    void saveChanges();

private:
    QList<AbstractData*> _sons;
};

#endif // CONTAINERDATA_H
