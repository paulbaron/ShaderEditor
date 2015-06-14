#include "DataStructureManager.hh"

DataStructureManager *DataStructureManager::_manager = NULL;

DataStructureManager *DataStructureManager::getManager()
{
    if (_manager == NULL)
        _manager = new DataStructureManager();
    return (_manager);
}

void DataStructureManager::addData(SInstance *toAdd)
{
    _root.addSon(toAdd);
}

void DataStructureManager::setCurrent(SInstance *current)
{
    _currentSelection = current;
}

void DataStructureManager::setCurrentNull()
{
    _currentSelection = NULL;
}

SInstance *DataStructureManager::getCurrent() const
{
    return (_currentSelection);
}

void DataStructureManager::removeCurrent()
{
    removeData(_currentSelection);
    setCurrentNull();
}

bool DataStructureManager::removeData(SInstance *toRm)
{
    return (_root.removeSon(toRm));
}

SInstance *DataStructureManager::getData(QString name)
{
    return (_root.getSon(name));
}

DataStructureManager::DataStructureManager()
{
    _currentSelection = NULL;
}
