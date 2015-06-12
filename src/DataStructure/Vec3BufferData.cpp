#include "Vec3BufferData.hh"
#include "View/Vec3BufferDataView.hh"

Vec3BufferData::Vec3BufferData()
{
    _view = new Vec3BufferDataView(this);
    bool create = _vbo.create();
    assert(create);
}

Vec3BufferData::~Vec3BufferData()
{
    _vbo.destroy();
}

void Vec3BufferData::saveChanges()
{
    Vec3BufferDataView *dataView = static_cast<Vec3BufferDataView*>(_view);
    glm::vec3 *data = dataView->getData();

    _count = dataView->getDataCount();
    _vbo.bind();
    _vbo.allocate(data, _count * 3 * sizeof(float));
}
