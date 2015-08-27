#ifndef GLMSERIALIZATION
#define GLMSERIALIZATION

#include <glm/glm.hpp>
#include <glm/gtc/vec1.hpp>

#include <boost/serialization/nvp.hpp>

namespace boost
{
    namespace serialization
    {

        template<class Archive>
        void serialize(Archive & ar, glm::uvec1 &value, const unsigned int version)
        {
            ar & boost::serialization::make_nvp("x", value.x);
        }

        template<class Archive>
        void serialize(Archive & ar, glm::vec1 &value, const unsigned int version)
        {
            ar & boost::serialization::make_nvp("x", value.x);
        }

        template<class Archive>
        void serialize(Archive & ar, glm::vec2 &value, const unsigned int version)
        {
            ar & boost::serialization::make_nvp("x", value.x)
                & boost::serialization::make_nvp("y", value.y);
        }

        template<class Archive>
        void serialize(Archive & ar, glm::vec3 &value, const unsigned int version)
        {
            ar & boost::serialization::make_nvp("x", value.x)
                & boost::serialization::make_nvp("y", value.y)
                & boost::serialization::make_nvp("z", value.z);
        }

        template<class Archive>
        void serialize(Archive & ar, glm::vec4 &value, const unsigned int version)
        {
            ar & boost::serialization::make_nvp("x", value.x)
                & boost::serialization::make_nvp("y", value.y)
                & boost::serialization::make_nvp("z", value.z)
                & boost::serialization::make_nvp("w", value.w);
        }

        template<class Archive>
        void serialize(Archive & ar, glm::bvec4 &value, const unsigned int version)
        {
            ar & boost::serialization::make_nvp("x", value.x)
                & boost::serialization::make_nvp("y", value.y)
                & boost::serialization::make_nvp("z", value.z)
                & boost::serialization::make_nvp("w", value.w);
        }

    } // namespace serialization
} // namespace boost

#endif // GLMSERIALIZATION

