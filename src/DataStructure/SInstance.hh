#ifndef SINSTANCE_H
#define SINSTANCE_H

#include <QString>
#include <QList>
#include <QTreeWidgetItem>

class AbstractData;

enum EInstanceType
{
    DATA_INSTANCE,
    CONTAINER_INSTANCE
};

class SContainerInstance;

class SInstance
{
    friend class SContainerInstance;
public:
    SInstance();
    SContainerInstance *getParent() const;
    EInstanceType getType() const;

    virtual void destroy() = 0;
    virtual QString getName() const = 0;
    virtual SInstance *copy() const = 0;
    virtual QTreeWidgetItem *getTreeItem() const = 0;

protected:
    SContainerInstance *_parent;
    EInstanceType _type;
};

class SContainerInstance : public SInstance
{
public:
    SContainerInstance();
    void addSon(SInstance *toAdd);
    bool removeSon(SInstance *toRm);
    SInstance *getSon(QString sonName) const;

    virtual void destroy();
    virtual QString getName() const;
    virtual SInstance *copy() const;
    virtual QTreeWidgetItem *getTreeItem() const;

private:
    QList<SInstance*> _instances;
    QString _name;
};

class SDataInstance : public SInstance
{
public:
    SDataInstance(AbstractData *data);
    AbstractData *getData() const;

    virtual void destroy();
    virtual QString getName() const;
    virtual SInstance *copy() const;
    virtual QTreeWidgetItem *getTreeItem() const;

private:
    AbstractData *_data;
};

#endif // SINSTANCE_H
