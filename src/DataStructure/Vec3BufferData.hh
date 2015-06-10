#ifndef VERTEXBUFFERDATA_H
#define VERTEXBUFFERDATA_H

#include "AbstractData.hh"

class Vec3BufferData : public AbstractData
{
public:
    Vec3BufferData();
    ~Vec3BufferData();

public slots:
    void saveChanges();
};

#endif // VERTEXBUFFERDATA_H
