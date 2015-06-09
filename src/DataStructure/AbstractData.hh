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

    AbstractData()
    {
        static int id = 0;
        _name = "Data " + QString::number(id++);
        _view = NULL;
    }

    virtual ~AbstractData() { }

    EDataTypes getType() const { return (_type); }

    virtual QWidget *getView() const { return (_view); }

    QString getName() const { return (_name); }
    void setName(QString name) { _name = name; }

public slots:
    virtual void saveChanges() = 0;

protected:
    AbstractData *_parent;
    QString _name;
    QWidget *_view;

private:
    const EDataTypes _type;
};

#endif // ABSTRACTDATA_H
