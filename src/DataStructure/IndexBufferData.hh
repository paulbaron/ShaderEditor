#ifndef INDEXBUFFERDATA_H
#define INDEXBUFFERDATA_H

#include "ABufferData.hh"

#include "View/BufferDataView.hpp"
#include "View/UintSpinBoxDelegate.hh"

#include "../GlmSerialization.hh"

#include <boost/serialization/vector.hpp>

class IndexBufferData : public ABufferData
{
public:
    IndexBufferData();
    ~IndexBufferData() { }

    virtual QString getInputType() const;
    virtual void setInput(QString inputName, GLSLShader &program, int textureNumber);

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ABufferData);
        BufferDataView<glm::uvec1, UintSpinBoxDelegate> *bufferView =
                static_cast<BufferDataView<glm::uvec1, UintSpinBoxDelegate>*>(_view);
        std::vector<glm::uvec1> buffer(bufferView->getDataCount());
        int i = 0;

        for (std::vector<glm::uvec1>::iterator it = buffer.begin();
             it != buffer.end();
             ++it)
        {
            *it = bufferView->getData()[i++];
        }
        ar & boost::serialization::make_nvp("bufferData", buffer);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        ar & BOOST_SERIALIZATION_BASE_OBJECT_NVP(ABufferData);
        BufferDataView<glm::uvec1, UintSpinBoxDelegate> *bufferView =
                static_cast<BufferDataView<glm::uvec1, UintSpinBoxDelegate>*>(_view);
        std::vector<glm::uvec1> buffer;

        ar & boost::serialization::make_nvp("bufferData", buffer);
        for (std::vector<glm::uvec1>::iterator it = buffer.begin();
             it != buffer.end();
             ++it)
        {
            bufferView->appendRow(*it);
        }
        saveChanges();
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

public slots:
    virtual void saveChanges();
};

#include <boost/serialization/export.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/archive/xml_oarchive.hpp>

BOOST_CLASS_EXPORT_KEY(IndexBufferData)

#endif // INDEXBUFFERDATA_H
