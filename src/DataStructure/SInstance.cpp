#include "SInstance.hh"
#include "AbstractData.hh"

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
            it = _instances.erase(it);
            return (true);
        }
        else if ((*it)->type == CONTAINER_INSTANCE)
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
        if ((*it)->type == DATA_INSTANCE)
        {
            SDataInstance *son = static_cast<SDataInstance*>(*it);

            if (son->_data->getName() == sonName)
            {
                return (son);
            }
        }
        else if ((*it)->type == CONTAINER_INSTANCE)
        {
            SContainerInstance *son = static_cast<SContainerInstance*>(*it);

            if (son->_name == sonName)
            {
                return (son);
            }
            else
            {
                SInstance ret = son->getSon(sonName);

                if (ret != NULL)
                {
                    return (ret);
                }
            }
        }
        ++it;
    }
    return (NULL);
}

SDataInstance::SDataInstance(AbstractData *data)
{
    _type = DATA_INSTANCE;
    _data = data;
}
