#ifndef RENDERPASS_H
#define RENDERPASS_H

#include <QVector>

#include "DataStructure/SInstance.hh"
#include "DataStructure/RenderTextureData.hh"

#include "OpenGLState.hh"
#include "GlslShader.hh"

#include <boost/serialization/nvp.hpp>
#include <boost/serialization/string.hpp>

namespace Ui {
class RenderPassUi;
}

class RenderPass
{
public:
    enum EOutputs
    {
        DEPTH_OUTPUT,
        DEPTH_STENCIL_OUTPUT,
        COLOR1_OUTPUT,
        COLOR2_OUTPUT,
        COLOR3_OUTPUT,
        COLOR4_OUTPUT,
        COLOR5_OUTPUT,
        COLOR6_OUTPUT,
        COLOR7_OUTPUT,
        NBR_OUTPUT
    };

    RenderPass();
    ~RenderPass();

    // Input
    void setInput(SInstance *toAdd);
    void removeInput(SInstance *toRm, bool freeMemory = false);
    SInstance *getInput(int inputId) const;
    // input selection
    void setCurrentInput(SInstance *current);
    void setCurrentInputNull();
    void removeCurrentInput(bool freeMemory = true);
    SInstance *getCurrentInput() const;
    // Output
    void setOutput(EOutputs attachment, RenderTextureData *rt);
    void unsetOutput(EOutputs attachment);
    RenderTextureData *getOutput(EOutputs attachment) const;
    // Shaders
    void setVertexCode(QString code);
    void setFragmentCode(QString code);
    // Render functions
    QString getOutputCode() const;
    void bindOutput();
    void renderGroup(SContainerInstance const *root);
    void render();
    // Update the OpenGL state
    void updateOpenGLState(Ui::RenderPassUi *ui);
    // Update the RenderPass UI
    void updateRenderPassUi(Ui::RenderPassUi *ui);
    // Remove a data from the inputs
    void removeData(AbstractData *data);

    template<class Archive>
    void save(Archive &ar, unsigned int version) const
    {
        std::string vertexCode, fragmentCode;

        vertexCode = _vertexCode.toStdString();
        fragmentCode = _fragmentCode.toStdString();
        ar & boost::serialization::make_nvp("vertexCode", vertexCode)
            & boost::serialization::make_nvp("fragmentCode", fragmentCode)
            & boost::serialization::make_nvp("width", _width)
            & boost::serialization::make_nvp("height", _height)
            & boost::serialization::make_nvp("outputs", _outputs)
            & boost::serialization::make_nvp("inputs", _root)
            & boost::serialization::make_nvp("openGlState", _state);
    }

    template<class Archive>
    void load(Archive &ar, unsigned int version)
    {
        std::string vertexCode, fragmentCode;

        ar & boost::serialization::make_nvp("vertexCode", vertexCode)
            & boost::serialization::make_nvp("fragmentCode", fragmentCode)
            & boost::serialization::make_nvp("width", _width)
            & boost::serialization::make_nvp("height", _height)
            & boost::serialization::make_nvp("outputs", _outputs)
            & boost::serialization::make_nvp("inputs", _root)
            & boost::serialization::make_nvp("openGlState", _state);
        _vertexCode = QString::fromStdString(vertexCode);
        _fragmentCode = QString::fromStdString(fragmentCode);
        _codeChanged = true;
        _currentSelection = NULL;

        for (int i = 0; i < NBR_OUTPUT; ++i)
        {
            if (_outputs[i] != NULL)
            {
                setOutput((EOutputs)i, _outputs[i]);
            }
        }
    }

    BOOST_SERIALIZATION_SPLIT_MEMBER()

private:
    // Shader code
    QString _vertexCode;
    QString _fragmentCode;
    bool _codeChanged;
    // Shader objects
    GLSLShader _shader;
    // FBO
    GLuint _fbo;
    // Contain the data IDs of the render texture
    RenderTextureData *_outputs[NBR_OUTPUT];
    GLuint _width, _height;
   // Inputs
    SContainerInstance _root;
    SInstance *_currentSelection;
    // OpenGL State
    OpenGLState _state;
};

#endif // RENDERPASS_H
