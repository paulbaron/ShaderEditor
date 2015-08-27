#ifndef ABUFFERDATA_H
#define ABUFFERDATA_H

#include "AbstractData.hh"

#include <QOpenGLBuffer>

class ABufferData : public AbstractData
{
public:
    ABufferData(QOpenGLBuffer::Type type = QOpenGLBuffer::VertexBuffer);
    ~ABufferData();

    int getCount() const { return (_count); }

    template<class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(AbstractData);
    }

protected:
    int _count;
    QOpenGLBuffer _vbo;
};

#include <boost/serialization/export.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

BOOST_CLASS_EXPORT_KEY(ABufferData)

#endif // ABUFFERDATA_H
