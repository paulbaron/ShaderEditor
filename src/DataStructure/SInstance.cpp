#include "SInstance.hh"
#include "AbstractData.hh"
#include "View/ContainerView.hh"

SInstance::SInstance()
{
    static int id = 0;

    _parent = NULL;
    _uniqueId = id++;
}

SContainerInstance *SInstance::getParent() const
{
    return (_parent);
}

EInstanceType SInstance::getType() const
{
    return (_type);
}

int SInstance::getInstanceId() const
{
    return (_uniqueId);
}

SContainerInstance::SContainerInstance()
{
    _type = CONTAINER_INSTANCE;
    _name = "Draw Group " + QString::number(_uniqueId);
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

SInstance *SContainerInstance::getSon(int instanceId) const
{
    QList<SInstance*>::const_iterator it = _instances.begin();

    while (it != _instances.end())
    {
        if ((*it)->getInstanceId() == instanceId)
        {
            return (*it);
        }
        else if ((*it)->getType() == CONTAINER_INSTANCE)
        {
            SContainerInstance *son = static_cast<SContainerInstance*>(*it);
            SInstance *ret = son->getSon(instanceId);

            if (ret != NULL)
            {
                return (ret);
            }
        }
        ++it;
    }
    return (NULL);
}

QList<SInstance*>::iterator SContainerInstance::begin()
{
    return (_instances.begin());
}

QList<SInstance*>::const_iterator SContainerInstance::begin() const
{
    return (_instances.begin());
}

QList<SInstance*>::iterator SContainerInstance::end()
{
    return (_instances.end());
}

QList<SInstance*>::const_iterator SContainerInstance::end() const
{
    return (_instances.end());
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

SInstance *SContainerInstance::copy() const
{
    SContainerInstance *ret = new SContainerInstance;
    QList<SInstance*>::const_iterator it = _instances.begin();

    while (it != _instances.end())
    {
        ret->addSon((*it)->copy());
        ++it;
    }
    return (ret);
}

QTreeWidgetItem *SContainerInstance::getTreeItem() const
{
    QTreeWidgetItem *item = new QTreeWidgetItem;
    QList<SInstance*>::const_iterator it = _instances.begin();

    item->setText(0, getName());
    item->setData(0, Qt::UserRole, _uniqueId);
    while (it != _instances.end())
    {
        item->addChild((*it)->getTreeItem());
        ++it;
    }
    return (item);
}

SDataInstance::SDataInstance(AbstractData *data)
{
    _type = DATA_INSTANCE;
    _data = data;
    _inputName = "uniformData" + QString::number(_uniqueId);
}

AbstractData *SDataInstance::getData() const
{
    return (_data);
}

void SDataInstance::setInputName(QString name)
{
    _inputName = name;
}

QString SDataInstance::getInputName() const
{
    return (_inputName);
}

int SDataInstance::setInput(QOpenGLShaderProgram *program) const
{
    return (_data->setInput(getInputName(), program));
}

void SDataInstance::destroy()
{
    delete _data;
}

QString SDataInstance::getName() const
{
    return (_data->getName());
}

SInstance *SDataInstance::copy() const
{
    return (new SDataInstance(_data));
}

QTreeWidgetItem *SDataInstance::getTreeItem() const
{
    QTreeWidgetItem *item = new QTreeWidgetItem;

    item->setText(0, getName());
    item->setText(1, getInputName());
    item->setData(0, Qt::UserRole, _uniqueId);
    return (item);
}
