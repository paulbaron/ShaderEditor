#include "AbstractData.hh"
#include "DataStructureManager.hh"

AbstractData::AbstractData(QString prefix)
{
    int id = 0;

    do
    {
        _name = prefix + QString::number(id++);
    } while (DataStructureManager::getManager()->getInstance(_name) != NULL);
    _view = NULL;
}

AbstractData::~AbstractData()
{
    delete _view;
}

AbstractData::EDataTypes AbstractData::getType() const
{
    return (_type);
}

QWidget *AbstractData::getView() const
{
    return (_view);
}

QString AbstractData::getName() const
{
    return (_name);
}

void AbstractData::setName(QString name)
{
    _name = name;
}
