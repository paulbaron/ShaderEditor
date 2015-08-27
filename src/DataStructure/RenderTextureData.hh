#ifndef TEXTUREDATA_H
#define TEXTUREDATA_H

#include "ATextureData.hh"
#include "View/RenderTextureDataView.hh"

class RenderTextureData : public ATextureData
{
public:
    RenderTextureData();
    ~RenderTextureData();

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ATextureData);
        ar & boost::serialization::make_nvp("format", _format)
            & boost::serialization::make_nvp("width", _width)
            & boost::serialization::make_nvp("height", _height);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ATextureData);
        ar & boost::serialization::make_nvp("format", _format)
            & boost::serialization::make_nvp("width", _width)
            & boost::serialization::make_nvp("height", _height);
        updateUi();
        updateOpenGLParameters();
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public slots:
    virtual void saveChanges();

private:
    GLenum getPixelFormatFromIndex(int idx) const;
    int getIndexFromPixelFormat(GLenum format) const;

    void updateUi();

    void getFormatInfo(GLenum internalFormat, GLenum &format, GLenum &type);
    void updateOpenGLParameters();
};

#include <boost/serialization/export.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

BOOST_CLASS_EXPORT_KEY(RenderTextureData)

#endif // TEXTUREDATA_H
