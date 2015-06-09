#ifndef MAT2DATA_H
#define MAT2DATA_H

#include "AbstractData.hh"
#include "../vendors/glm/glm.hpp"

class Mat2Data : public AbstractData
{
public:
    Mat2Data();
    ~Mat2Data();

    QWidget *getTypeEditor();

public slots:
    void saveChanges();

private:
    glm::mat2 _value;
};

#endif // MAT2DATA_H
