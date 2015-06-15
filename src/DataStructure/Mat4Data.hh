#ifndef MAT4DATA_H
#define MAT4DATA_H

#include "AbstractData.hh"
#include "../vendors/glm/glm.hpp"

class Mat4Data : public AbstractData
{
public:
    Mat4Data();
    ~Mat4Data();

    QString getInputType() const;
    int setInput(QString inputName, QOpenGLShaderProgram *program);

public slots:
    void saveChanges();

private:
    glm::mat4 _matrix;
};

#endif // MAT4DATA_H
