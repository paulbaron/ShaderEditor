#ifndef ABSTRACTDATA_H
#define ABSTRACTDATA_H

#include <QWidget>
#include <QObject>
#include "GlslShader.hh"

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

class ContainerData;

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
        DATA_RENDER_TEXTURE,
        DATA_LOADED_TEXTURE,
        DATA_VERTEX_BUFFER,
        DATA_INDEX_BUFFER,
        DATA_FLOAT,
        DATA_VEC2,
        DATA_VEC3,
        DATA_VEC4
    };

    AbstractData(QString prefix = "Data_");
    virtual ~AbstractData();

    EDataTypes getType() const;
    QWidget *getView() const;
    QString getName() const;
    void setName(QString name);

    virtual QString getInputType() const = 0;
    virtual void setInput(QString inputName, GLSLShader &program, int textureNumber) = 0;

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        std::string name(_name.toStdString());

        ar & boost::serialization::make_nvp("name", name)
            & boost::serialization::make_nvp("type", _type);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        std::string name;

        ar & boost::serialization::make_nvp("name", name)
            & boost::serialization::make_nvp("type", _type);
        _name = QString::fromStdString(name);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public slots:
    virtual void saveChanges() = 0;

protected:
    QString _name;
    QWidget *_view;
    EDataTypes _type;
};

#endif // ABSTRACTDATA_H
