#include "DataStructureManager.hh"
#include "ContainerData.hh"

DataStructureManager *DataStructureManager::_manager = NULL;

DataStructureManager *DataStructureManager::getManager()
{
    if (_manager == NULL)
        _manager = new DataStructureManager();
    return (_manager);
}

void DataStructureManager::addData(AbstractData *toAdd)
{
    _dataStructures.append(toAdd);
}

void DataStructureManager::setCurrent(AbstractData *current)
{
    _currentSelection = current;
}

void DataStructureManager::setCurrentNull()
{
    _currentSelection = NULL;
}

AbstractData *DataStructureManager::getCurrent() const
{
    return (_currentSelection);
}

void DataStructureManager::removeCurrent()
{
    removeData(_currentSelection);
    _currentSelection = NULL;
}

void DataStructureManager::removeData(AbstractData *toRm)
{
    QList<AbstractData*>::iterator it = _dataStructures.begin();
    bool removed = false;

    while (it != _dataStructures.end() && removed == false)
    {
        if (toRm == *it)
        {
            _dataStructures.erase(it);
            removed = true;
        }
        else if ((*it)->getType() == AbstractData::DATA_CONTAINER)
        {
            ContainerData *container = static_cast<ContainerData*>(*it);

            if (container->removeSon(toRm))
            {
                removed = true;
            }
        }
        ++it;
    }
}

AbstractData *DataStructureManager::getData(QString name)
{
    QList<AbstractData*>::const_iterator it = _dataStructures.begin();

    while (it != _dataStructures.end())
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

DataStructureManager::DataStructureManager()
{
    _currentSelection = NULL;
}
