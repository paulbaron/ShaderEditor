#ifndef OPENGLSTATE_H
#define OPENGLSTATE_H

#include "GlmSerialization.hh"

#include <QOpenGLContext>

#include <boost/serialization/nvp.hpp>

namespace Ui {
class RenderPassUi;
}

class OpenGLState
{
public:
    OpenGLState();
    ~OpenGLState() { }

    void updateOpenGLState(Ui::RenderPassUi *ui);
    void updateUiState(Ui::RenderPassUi *ui);

    void setOpenGLState();

    template<class Archive>
    void serialize(Archive &ar, unsigned int version)
    {
        ar & boost::serialization::make_nvp("colorWriteMask", _colorWriteMask)
            & boost::serialization::make_nvp("depthTest", _depthTest)
            & boost::serialization::make_nvp("depthMask", _depthMask)
            & boost::serialization::make_nvp("depthFunc", _depthFunc)
            & boost::serialization::make_nvp("clearColor", _clearColor)
            & boost::serialization::make_nvp("clearColorBuffer", _clearColorBuffer)
            & boost::serialization::make_nvp("clearDepth", _clearDepth)
            & boost::serialization::make_nvp("clearDepthBuffer", _clearDepthBuffer)
            & boost::serialization::make_nvp("clearStencil", _clearStencil)
            & boost::serialization::make_nvp("clearStencilBuffer", _clearStencilBuffer)
            & boost::serialization::make_nvp("enableBlending", _enableBlending)
            & boost::serialization::make_nvp("rgbBlendEq", _rgbBlendEq)
            & boost::serialization::make_nvp("rgbSrcOp", _rgbSrcOp)
            & boost::serialization::make_nvp("rgbDstOp", _rgbDstOp)
            & boost::serialization::make_nvp("alphaBlendEq", _alphaBlendEq)
            & boost::serialization::make_nvp("alphaSrcOp", _alphaSrcOp)
            & boost::serialization::make_nvp("alphaDstOp", _alphaDstOp)
            & boost::serialization::make_nvp("enableCulling", _enableCulling)
            & boost::serialization::make_nvp("cullingMode", _cullingMode)
            & boost::serialization::make_nvp("stencilMask", _stencilMask)
            & boost::serialization::make_nvp("enableStencilTest", _enableStencilTest)
            & boost::serialization::make_nvp("backFaceStencilFunc", _backFaceStencilFunc)
            & boost::serialization::make_nvp("backFaceStencilRef", _backFaceStencilRef)
            & boost::serialization::make_nvp("backFaceStencilFails", _backFaceStencilFails)
            & boost::serialization::make_nvp("backFaceDepthFails", _backFaceDepthFails)
            & boost::serialization::make_nvp("backFaceStencilPass", _backFaceStencilPass)
            & boost::serialization::make_nvp("frontFaceStencilFunc", _frontFaceStencilFunc)
            & boost::serialization::make_nvp("frontFaceStencilRef", _frontFaceStencilRef)
            & boost::serialization::make_nvp("frontFaceStencilFails", _frontFaceStencilFails)
            & boost::serialization::make_nvp("frontFaceDepthFails", _frontFaceDepthFails)
            & boost::serialization::make_nvp("frontFaceStencilPass", _frontFaceStencilPass);
    }

private:
    // Useful functions
    GLenum getDepthStencilTest(int test);
    GLenum getBlendEq(int eq);
    GLenum getBlendFunc(int func);
    GLenum getCullingMode(int mode);
    GLenum getStencilOp(int op);

    // Color
    glm::bvec4 _colorWriteMask;
    // Depth
    bool _depthTest;
    bool _depthMask;
    int _depthFunc;
    // Clear
    glm::vec4 _clearColor;
    bool _clearColorBuffer;
    float _clearDepth;
    bool _clearDepthBuffer;
    int _clearStencil;
    bool _clearStencilBuffer;
    // Blending
    bool _enableBlending;
    int _rgbBlendEq;
    int _rgbSrcOp;
    int _rgbDstOp;
    int _alphaBlendEq;
    int _alphaSrcOp;
    int _alphaDstOp;
    // Culling
    bool _enableCulling;
    int _cullingMode;
    // Stencil
    bool _stencilMask;
    bool _enableStencilTest;
    int _backFaceStencilFunc;
    int _backFaceStencilRef;
    int _backFaceStencilFails;
    int _backFaceDepthFails;
    int _backFaceStencilPass;
    int _frontFaceStencilFunc;
    int _frontFaceStencilRef;
    int _frontFaceStencilFails;
    int _frontFaceDepthFails;
    int _frontFaceStencilPass;
};

#endif // OPENGLSTATE_H
