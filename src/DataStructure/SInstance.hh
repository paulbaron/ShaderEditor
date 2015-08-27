#ifndef SINSTANCE_H
#define SINSTANCE_H

#include "GlslShader.hh"

#include <QString>
#include <QList>
#include <QTreeWidgetItem>
#include <QOpenGLShaderProgram>

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/list.hpp>
#include <boost/serialization/string.hpp>

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
    virtual ~SInstance() { }
    SContainerInstance *getParent() const;
    EInstanceType getType() const;
    int getInstanceId() const;

    virtual QString getName() const = 0;
    virtual SInstance *copy() const = 0;
    virtual QTreeWidgetItem *getTreeItem() const = 0;

    template<class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        ar & boost::serialization::make_nvp("parent", _parent)
            & boost::serialization::make_nvp("type", _type);
    }

protected:
    SContainerInstance *_parent;
    EInstanceType _type;
    int _uniqueId;
};

class SDataInstance : public SInstance
{
public:
    SDataInstance(AbstractData *data = NULL);
    virtual ~SDataInstance() { }
    AbstractData *getData() const;

    void setTextureBinding(int binding);

    void setInputName(QString name);
    QString getInputName() const;
    void setInput(GLSLShader &program) const;

    virtual QString getName() const;
    virtual SInstance *copy() const;
    virtual QTreeWidgetItem *getTreeItem() const;

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        std::string inputName(_inputName.toStdString());

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SInstance);
        ar & boost::serialization::make_nvp("inputName", inputName)
            & boost::serialization::make_nvp("data", _data);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        std::string inputName;

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SInstance);
        ar & boost::serialization::make_nvp("inputName", inputName)
            & boost::serialization::make_nvp("data", _data);
        _inputName = QString::fromStdString(inputName);
        _textureBinding = 0;
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

private:
    QString _inputName;
    AbstractData *_data;
    int _textureBinding;
};

class SContainerInstance : public SInstance
{
public:
    SContainerInstance();
    virtual ~SContainerInstance() { }
    void addSon(SInstance *toAdd);
    bool removeSon(SInstance *toRm);
    void removeSonsData(AbstractData *data);
    SInstance *getSon(QString sonName) const;
    SInstance *getSon(int instanceId) const;
    QList<SInstance*>::iterator begin();
    QList<SInstance*>::const_iterator begin() const;
    QList<SInstance*>::iterator end();
    QList<SInstance*>::const_iterator end() const;
    void clearAll();

    virtual QString getName() const;
    virtual SInstance *copy() const;
    virtual QTreeWidgetItem *getTreeItem() const;

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        std::list<SInstance*> instances(_instances.toStdList());
        std::string name(_name.toStdString());

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SInstance);
        ar.register_type(static_cast<SDataInstance*>(NULL));
        ar.register_type(static_cast<SContainerInstance*>(NULL));
        ar & boost::serialization::make_nvp("instances", instances)
            & boost::serialization::make_nvp("name", name);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        std::list<SInstance*> instances;
        std::string name;

        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(SInstance);
        ar.register_type(static_cast<SDataInstance*>(NULL));
        ar.register_type(static_cast<SContainerInstance*>(NULL));
        ar & boost::serialization::make_nvp("instances", instances)
            & boost::serialization::make_nvp("name", name);
        _instances = QList<SInstance*>::fromStdList(instances);
        _name = QString::fromStdString(name);
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

private:
    QList<SInstance*> _instances;
    QString _name;
};

#endif // SINSTANCE_H
