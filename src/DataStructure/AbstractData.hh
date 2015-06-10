#ifndef ABSTRACTDATA_H
#define ABSTRACTDATA_H

#include <QWidget>
#include <QObject>

class AbstractData : public QObject
{
    Q_OBJECT

public:
    enum EDataTypes
    {
        DATA_VECTOR,
        DATA_MAT2,
        DATA_MAT3,
        DATA_MAT4,
        DATA_TEXTURE,
        DATA_VERTEX_BUFFER,
        DATA_CONTAINER
    };

    AbstractData();
    virtual ~AbstractData();

    EDataTypes getType() const;
    QWidget *getView() const;
    QString getName() const;
    void setName(QString name);

public slots:
    virtual void saveChanges() = 0;

protected:
    AbstractData *_parent;
    QString _name;
    QWidget *_view;
    EDataTypes _type;
};

#endif // ABSTRACTDATA_H
