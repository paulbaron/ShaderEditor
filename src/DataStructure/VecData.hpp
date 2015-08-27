#ifndef VECDATA_HPP
#define VECDATA_HPP

#include "AbstractData.hh"
#include "View/VecView.hpp"

#include "GlmSerialization.hh"

template<class GlmVec>
class VecData : public AbstractData
{
public:
    VecData() :
        AbstractData((GlmVec().length() == 1) ?
                     ("Float_") :
                     ("Vec" + QString::number(GlmVec().length()) + "_"))
    {
        _type = static_cast<AbstractData::EDataTypes>(DATA_FLOAT + GlmVec().length() - 1);
        _view = new VecView<GlmVec>(this);
        saveChanges();
    }

    ~VecData()
    {
    }

    virtual QString getInputType() const
    {
        if (_vec.length() == 1)
        {
            return ("uniform float");
        }
        else
        {
            return ("uniform vec" + QString::number(_vec.length()));
        }
    }

    virtual void setInput(QString inputName, GLSLShader &program, int textureNumber)
    {
        program.setUniform(inputName, _vec);
    }

    template<class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(AbstractData);
        ar & boost::serialization::make_nvp("vector", _vec);
        static_cast<VecView<GlmVec>*>(_view)->setUi(_vec);
    }


public slots:
    virtual void saveChanges()
    {
        VecView<GlmVec> *dataView = static_cast<VecView<GlmVec>*>(_view);

        _vec = dataView->getValue();
    }

private:
    GlmVec _vec;
};

#include <boost/serialization/export.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

BOOST_CLASS_EXPORT_KEY(VecData<glm::vec1>)
BOOST_CLASS_EXPORT_KEY(VecData<glm::vec2>)
BOOST_CLASS_EXPORT_KEY(VecData<glm::vec3>)
BOOST_CLASS_EXPORT_KEY(VecData<glm::vec4>)


#endif // VECDATA_HPP
