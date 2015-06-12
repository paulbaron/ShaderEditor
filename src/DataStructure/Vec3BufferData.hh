#ifndef VERTEXBUFFERDATA_H
#define VERTEXBUFFERDATA_H

#include "AbstractData.hh"
#include <QOpenGLBuffer>

class Vec3BufferData : public AbstractData
{
public:
    Vec3BufferData();
    ~Vec3BufferData();

public slots:
    void saveChanges();

private:
    int _count;
    QOpenGLBuffer _vbo;
};

#endif // VERTEXBUFFERDATA_H
