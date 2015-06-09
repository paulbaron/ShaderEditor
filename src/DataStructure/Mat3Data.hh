#ifndef MAT3DATA_H
#define MAT3DATA_H

#include "AbstractData.hh"

class Mat3Data : public AbstractData
{
public:
    Mat3Data();
    ~Mat3Data();

    QWidget *getTypeEditor();

public slots:
    void saveChanges();

};

#endif // MAT3DATA_H
