#include "DataStructureManager.hh"


DataStructureManager *DataStructureManager::getManager()
{
    if (_manager == NULL)
        _manager = new DataStructureManager();
    return (_manager);
}

void DataStructureManager::addData(AbstractData *toAdd)
{

}

void DataStructureManager::setCurrent(QString name)
{

}

void DataStructureManager::setCurrentNull()
{

}

void DataStructureManager::removeCurrent()
{

}

bool DataStructureManager::contains(QString name)
{

}

DataStructureManager::DataStructureManager()
{

}
