#ifndef VECTORDATA_H
#define VECTORDATA_H

#include "AbstractData.hh"

class VectorData : public AbstractData
{
public:
    VectorData();

public slots:
    void saveChanges();
};

#endif // VECTORDATA_H
