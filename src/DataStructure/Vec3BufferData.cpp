#include "Vec3BufferData.hh"
#include "View/Vec3BufferDataView.hh"

Vec3BufferData::Vec3BufferData()
{
    _type = DATA_VERTEX_BUFFER;
    _view = new Vec3BufferDataView(this);
    bool create = _vbo.create();
    assert(create);
}

Vec3BufferData::~Vec3BufferData()
{
    _vbo.destroy();
}

QString Vec3BufferData::getInputType() const
{
    return ("attribute vec3");
}

int Vec3BufferData::setInput(QString inputName, QOpenGLShaderProgram *program)
{
    _vbo.bind();
    program->enableAttributeArray(inputName.toStdString().c_str());
    program->setAttributeBuffer(inputName.toStdString().c_str(), GL_FLOAT, 0, 3);
    return (_count);
}

void Vec3BufferData::saveChanges()
{
    Vec3BufferDataView *dataView = static_cast<Vec3BufferDataView*>(_view);
    glm::vec3 *data = dataView->getData();

    _count = dataView->getDataCount();
    _vbo.bind();
    _vbo.allocate(data, _count * 3 * sizeof(float));
}
