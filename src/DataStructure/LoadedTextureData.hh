#ifndef LOADEDTEXTUREDATA_H
#define LOADEDTEXTUREDATA_H

#include "ATextureData.hh"

#include <QDir>

#include <boost/serialization/string.hpp>

class LoadedTextureData : public ATextureData
{
public:
    LoadedTextureData();
    virtual ~LoadedTextureData();

    void loadTexture(QString filePath);

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ATextureData);
        std::string relativePath = QDir::current().relativeFilePath(_texturePath).toStdString();
        ar & boost::serialization::make_nvp("texturePath", relativePath);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ATextureData);
        std::string texturePath;
        ar & boost::serialization::make_nvp("texturePath", texturePath);
        _texturePath = QDir::current().absoluteFilePath(QString(texturePath.c_str()));
        loadTexture(_texturePath);
        updateUi();
        saveChanges();
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public slots:
    virtual void saveChanges();

private:
    void updateUi();
    void updateOpenGLParameters();

    static bool _devilLoaded;

    QString _texturePath;
};

#include <boost/serialization/export.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

BOOST_CLASS_EXPORT_KEY(LoadedTextureData)

#endif // LOADEDTEXTUREDATA_H
