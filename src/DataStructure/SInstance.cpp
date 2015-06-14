#include "SInstance.hh"
#include "AbstractData.hh"
#include "View/ContainerView.hh"

SInstance::SInstance()
{
    _parent = NULL;
}

SContainerInstance *SInstance::getParent() const
{
    return (_parent);
}

EInstanceType SInstance::getType() const
{
    return (_type);
}

SContainerInstance::SContainerInstance()
{
    static int idx = 0;

    _type = CONTAINER_INSTANCE;
    _name = "Draw Group " + QString::number(idx++);
}

void SContainerInstance::addSon(SInstance *toAdd)
{
    _instances.push_back(toAdd);
    toAdd->_parent = this;
}

bool SContainerInstance::removeSon(SInstance *toRm)
{
    QList<SInstance*>::iterator it = _instances.begin();

    while (it != _instances.end())
    {
        if (*it == toRm)
        {
            (*it)->_parent = NULL;
            it = _instances.erase(it);
            return (true);
        }
        else if ((*it)->getType() == CONTAINER_INSTANCE)
        {
            SContainerInstance *container = static_cast<SContainerInstance*>(*it);

            if (container->removeSon(toRm) == true)
            {
                return (true);
            }
        }
        ++it;
    }
    return (false);
}

SInstance *SContainerInstance::getSon(QString sonName) const
{
    QList<SInstance*>::const_iterator it = _instances.begin();

    while (it != _instances.end())
    {
        if ((*it)->getName() == sonName)
        {
            return (*it);
        }
        else if ((*it)->getType() == CONTAINER_INSTANCE)
        {
            SContainerInstance *son = static_cast<SContainerInstance*>(*it);
            SInstance *ret = son->getSon(sonName);

            if (ret != NULL)
            {
                return (ret);
            }
        }
        ++it;
    }
    return (NULL);
}

void SContainerInstance::destroy()
{
    QList<SInstance*>::iterator it = _instances.begin();

    while (it != _instances.end())
    {
        (*it)->destroy();
        ++it;
    }
}

QString SContainerInstance::getName() const
{
    return (_name);
}

SDataInstance::SDataInstance(AbstractData *data)
{
    _type = DATA_INSTANCE;
    _data = data;
}

AbstractData *SDataInstance::getData() const
{
    return (_data);
}

void SDataInstance::destroy()
{
    delete _data;
}

QString SDataInstance::getName() const
{
    return (_data->getName());
}
