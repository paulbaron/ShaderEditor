#include "AbstractData.hh"
#include "DataStructureManager.hh"

AbstractData::AbstractData()
{
    static int id = 0;

    do
    {
        _name = "Data_" + QString::number(id++);
    } while (DataStructureManager::getManager()->getData(_name).data != NULL);
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
