#include "ContainerData.hh"
#include "DataStructureManager.hh"
#include "View/ContainerView.hh"
#include "ui_ContainerView.h"

ContainerData::ContainerData(bool &addSon, bool &removeSon)
{
    _view = new ContainerView(addSon, removeSon);
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

void ContainerData::addSon(AbstractData *toAdd)
{
    _sons.append(toAdd);
}

bool ContainerData::removeSon(AbstractData *toRm)
{
    QList<AbstractData*>::iterator it = _sons.begin();

    while (it != _sons.end())
    {
        if (*it == toRm)
        {
            _sons.erase(it);
            return (true);
        }
        else if ((*it)->getType() == AbstractData::DATA_CONTAINER)
        {
            ContainerData *container = static_cast<ContainerData*>(*it);

            if (container->removeSon(toRm))
            {
                return (true);
            }
        }
        ++it;
    }
    return (false);
}

AbstractData *ContainerData::getData(QString name) const
{
    QList<AbstractData*>::const_iterator it = _sons.begin();

    while (it != _sons.end())
    {
        if ((*it)->getName() == name)
        {
            return (*it);
        }
        else if ((*it)->getType() == AbstractData::DATA_CONTAINER)
        {
            ContainerData *container = static_cast<ContainerData*>(*it);

            AbstractData *retData = container->getData(name);

            if (retData != NULL)
            {
                return (retData);
            }
        }
        ++it;
    }
    return (NULL);
}

void ContainerData::saveChanges()
{

}
