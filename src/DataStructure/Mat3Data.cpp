#include "Mat3Data.hh"

Mat3Data::Mat3Data()
{

}

Mat3Data::~Mat3Data()
{

}

QString Mat3Data::getInputType() const
{
    return ("uniform mat3");
}

int Mat3Data::setInput(QString inputName, QOpenGLShaderProgram *program)
{
    return (0);
}

void Mat3Data::saveChanges()
{

}
