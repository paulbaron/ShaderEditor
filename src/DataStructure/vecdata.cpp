
#include "VecData.hpp"

#include <boost/serialization/export.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

BOOST_CLASS_EXPORT_IMPLEMENT(VecData<glm::vec1>)
BOOST_CLASS_EXPORT_IMPLEMENT(VecData<glm::vec2>)
BOOST_CLASS_EXPORT_IMPLEMENT(VecData<glm::vec3>)
BOOST_CLASS_EXPORT_IMPLEMENT(VecData<glm::vec4>)
