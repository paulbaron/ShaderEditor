#include "DataStructureManager.hh"

#include "AbstractData.hh"

DataStructureManager *DataStructureManager::_manager = NULL;

DataStructureManager *DataStructureManager::getManager()
{
    if (_manager == NULL)
        _manager = new DataStructureManager();
    return (_manager);
}

SDataInstance *DataStructureManager::addData(AbstractData *toAdd)
{
    SDataInstance *instance = new SDataInstance(toAdd);
    _root.addSon(instance);
    return (instance);
}

SContainerInstance *DataStructureManager::addContainer()
{
    SContainerInstance *toAdd = new SContainerInstance();
    _root.addSon(toAdd);
    return (toAdd);
}

void DataStructureManager::setCurrent(int id)
{
    _currentSelection = getInstance(id);
    emit currentSelectionChanged(_currentSelection);
}

void DataStructureManager::setCurrentNull()
{
    _currentSelection = NULL;
    emit currentSelectionChanged(_currentSelection);
}

SInstance *DataStructureManager::getCurrent() const
{
    return (_currentSelection);
}

void DataStructureManager::removeCurrent(bool freeMemory)
{
    removeInstance(_currentSelection, freeMemory);
    setCurrentNull();
}

void DataStructureManager::removeInstance(SInstance *toRm, bool freeMemory)
{
    if (toRm->getType() == DATA_INSTANCE)
    {
        SDataInstance *data = static_cast<SDataInstance*>(toRm);

        if (freeMemory)
        {
            delete data->getData();
        }
        _root.removeSon(toRm);
    }
    else if (toRm->getType() == CONTAINER_INSTANCE)
    {
        if (freeMemory)
        {
            SContainerInstance *container = static_cast<SContainerInstance*>(toRm);
            QList<SInstance*>::iterator it = container->begin();

            while (it != container->end())
            {
                removeInstance(*it);
                ++it;
            }
        }
        _root.removeSon(toRm);
    }
    if (freeMemory)
        delete toRm;
}

SContainerInstance const &DataStructureManager::getRoot() const
{
    return (_root);
}

SInstance *DataStructureManager::getInstance(int id)
{
    return (_root.getSon(id));
}

SInstance *DataStructureManager::getInstance(QString name)
{
    return (_root.getSon(name));
}

AbstractData *DataStructureManager::getData(int id)
{
    QMap<int, AbstractData*>::const_iterator it = _dataCollection.find(id);

    if (it != _dataCollection.end())
        return (it.value());
    return (NULL);
}

void DataStructureManager::clearAll()
{
    for (QMap<int, AbstractData*>::const_iterator it = _dataCollection.begin();
         it != _dataCollection.end();
         ++it)
    {
        delete it.value();
    }
    _dataCollection.clear();
    _root.clearAll();
    _currentSelection = NULL;
}

DataStructureManager::DataStructureManager()
{
    _currentSelection = NULL;
}
