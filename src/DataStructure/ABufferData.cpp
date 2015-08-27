#include "ABufferData.hh"

#include <assert.h>

BOOST_CLASS_EXPORT_IMPLEMENT(ABufferData)

ABufferData::ABufferData(QOpenGLBuffer::Type type) :
    AbstractData("Buffer_"),
    _vbo(type)
{
    if (type == QOpenGLBuffer::VertexBuffer)
        _type = DATA_VERTEX_BUFFER;
    else if (type == QOpenGLBuffer::IndexBuffer)
        _type = DATA_INDEX_BUFFER;
    bool create = _vbo.create();
    assert(create);
}

ABufferData::~ABufferData()
{
    _vbo.destroy();
}
