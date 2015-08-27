#ifndef ATEXTUREDATA_H
#define ATEXTUREDATA_H

#include "AbstractData.hh"

class ATextureData : public AbstractData
{
public:
    ATextureData(QString prefix);
    virtual ~ATextureData();

    GLenum getInternalFormat() const;
    GLuint getTextureId() const;

    GLuint getWidth() const;
    GLuint getHeight() const;

    virtual QString getInputType() const;
    virtual void setInput(QString inputName, GLSLShader &program, int textureBinding);

    template<class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(AbstractData);
        ar & boost::serialization::make_nvp("magFilter", _magFilter)
            & boost::serialization::make_nvp("minFilter", _minFilter)
            & boost::serialization::make_nvp("verticalWrapMode", _verticalWrapMode)
            & boost::serialization::make_nvp("horizontalWrapMode", _horizontalWrapMode);
    }

protected:
    // Useful functions
    GLenum getWrapModeFromIndex(int idx) const;
    int getIndexFromWrapMode(GLenum format) const;
    GLenum getFilterModeFromIndex(int idx) const;
    int getIndexFromFilterMode(GLenum format) const;

    // Actual texture data
    GLuint _id;
    GLenum _format;
    GLenum _magFilter;
    GLenum _minFilter;
    GLenum _verticalWrapMode;
    GLenum _horizontalWrapMode;
    GLuint _width;
    GLuint _height;

};

#include <boost/serialization/export.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

BOOST_CLASS_EXPORT_KEY(ATextureData)

#endif // ATEXTUREDATA_H
