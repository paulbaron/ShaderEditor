#include "Vec3BufferData.hh"
#include "View/Vec3BufferDataView.hh"

Vec3BufferData::Vec3BufferData()
{
    _view = new Vec3BufferDataView;
}

Vec3BufferData::~Vec3BufferData()
{
}

void Vec3BufferData::saveChanges()
{
}
