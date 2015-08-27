#ifndef MAT4DATA_H
#define MAT4DATA_H

#include "AbstractData.hh"

#include "../GlmSerialization.hh"

#include "View/Mat4DataView.hh"

class Mat4Data : public AbstractData
{
public:
    Mat4Data();
    ~Mat4Data();

    QString getInputType() const;
    void setInput(QString inputName, GLSLShader &program, int textureNumber);

    template<class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(AbstractData);
        ar & boost::serialization::make_nvp("matrixType", _matType);
        switch (_matType)
        {
        case Mat4DataView::Transform:
            {
                ar & boost::serialization::make_nvp("position", _position)
                    & boost::serialization::make_nvp("rotation", _rotation)
                    & boost::serialization::make_nvp("scale", _scale);
            }
            break;
        case Mat4DataView::LookAt:
            {
                ar & boost::serialization::make_nvp("eye", _eye)
                    & boost::serialization::make_nvp("center", _center)
                    & boost::serialization::make_nvp("up", _up);
            }
            break;
        case Mat4DataView::Perspective:
            {
                ar & boost::serialization::make_nvp("fov", _fov)
                    & boost::serialization::make_nvp("ratio", _ratio)
                    & boost::serialization::make_nvp("near", _near)
                    & boost::serialization::make_nvp("far", _far);
            }
            break;
        default:
            break;
        }
        ar & boost::serialization::make_nvp("invert", _invert);
        setUi();
    }

public slots:
    void saveChanges();

private:
    void setUi();
    // For serialization
    Mat4DataView::EMatrixType _matType;

    // If perspective type
    float _fov;
    glm::vec2 _ratio;
    float _near;
    float _far;

    // If transform type
    glm::vec3 _position;
    glm::vec3 _rotation;
    glm::vec3 _scale;

    // If look at type
    glm::vec3 _eye;
    glm::vec3 _center;
    glm::vec3 _up;

    bool _invert;

    glm::mat4 _matrix;
};

#include <boost/serialization/export.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

BOOST_CLASS_EXPORT_KEY(Mat4Data)

#endif // MAT4DATA_H
