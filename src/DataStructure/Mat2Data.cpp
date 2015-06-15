#include "Mat2Data.hh"

Mat2Data::Mat2Data()
{

}

Mat2Data::~Mat2Data()
{

}

QString Mat2Data::getInputType() const
{
    return ("uniform mat2");
}

int Mat2Data::setInput(QString inputName, QOpenGLShaderProgram *program)
{
    return (0);
}

void Mat2Data::saveChanges()
{

}
