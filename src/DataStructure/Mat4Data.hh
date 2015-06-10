#ifndef MAT4DATA_H
#define MAT4DATA_H

#include "AbstractData.hh"

class Mat4Data : public AbstractData
{
public:
    Mat4Data();
    ~Mat4Data();

public slots:
    void saveChanges();
};

#endif // MAT4DATA_H
