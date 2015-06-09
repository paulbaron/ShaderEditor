#include "ContainerData.hh"
#include "DataStructureManager.hh"

ContainerData::ContainerData()
{

}

ContainerData::~ContainerData()
{
    QList<AbstractData*>::const_iterator it = _sons.begin();

    while (it != _sons.end())
    {
        delete *it;
        ++it;
    }
}

bool ContainerData::addSon(AbstractData *toAdd)
{
//    if (DataStructureManager::getManager()->contains(toAdd->getName()))
}

void ContainerData::removeSon(AbstractData *toRm)
{

}
