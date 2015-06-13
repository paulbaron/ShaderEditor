#ifndef SDATAINSTANCE_H
#define SINSTANCE_H

#include <QString>
#include <QList>

class AbstractData;

enum EInstanceType
{
    DATA_INSTANCE,
    CONTAINER_INSTANCE
};

class SContainerInstance;

class SInstance
{
public:
    SInstance();
    SContainerInstance *getParent() const;
    EInstanceType getType() const;

protected:
    SContainerInstance *_parent;

private:
    EInstanceType _type;
};

class SContainerInstance : public SInstance
{
public:
    SContainerInstance();
    void addSon(SInstance *toAdd);
    bool removeSon(SIntance *toRm);
    SInstance *getSon(QString sonName) const;

private:
    QList<SInstance*> _instances;
    QString _name;
};

struct SDataInstance : public SInstance
{
public:
    SDataInstance(AbstractData *data);
    AbstractData *getData() const;

private:
    AbstractData *_data;
};

#endif // SINSTANCE_H
