#include "OpenGLState.hh"

#include "RenderPassManager.hh"
#include "RenderPass.hh"
#include "ui_RenderPassUi.h"

#include "QtOpenGLFunctions.hh"

OpenGLState::OpenGLState()
{
    // Color
    _colorWriteMask = glm::bvec4(true);
    // Depth
    _depthTest = true;
    _depthMask = true;
    _depthFunc = 1;
    // Clear
    _clearColor = glm::vec4(0);
    _clearColorBuffer = true;
    _clearDepth = 1.0f;
    _clearDepthBuffer = true;
    _clearStencil = 0;
    _clearStencilBuffer = false;
    // Blending
    _enableBlending = false;
    _rgbBlendEq = 0;
    _rgbSrcOp = 1;
    _rgbDstOp = 0;
    _alphaBlendEq = 0;
    _alphaSrcOp = 1;
    _alphaDstOp = 0;
    // Culling
    _enableCulling = false;
    _cullingMode = 1;
    // Stencil
    _stencilMask = false;
    _enableStencilTest = false;
    _backFaceStencilFunc = 7;
    _backFaceStencilRef = 0;
    _backFaceStencilFails = 0;
    _backFaceDepthFails = 0;
    _backFaceStencilPass = 0;
    _frontFaceStencilFunc = 7;
    _frontFaceStencilRef = 0;
    _frontFaceStencilFails = 0;
    _frontFaceDepthFails = 0;
    _frontFaceStencilPass = 0;
}

void OpenGLState::updateOpenGLState(Ui::RenderPassUi *ui)
{
    // Color
    _colorWriteMask = glm::bvec4(ui->redWrite_3->isChecked(),
                                 ui->greenWrite_3->isChecked(),
                                 ui->blueWrite_3->isChecked(),
                                 ui->alphaWrite_3->isChecked());
    // Depth
    _depthTest = ui->enableDepthTest_3->isChecked();
    _depthMask = ui->writeDepth_3->isChecked();
    _depthFunc = ui->depthFunc_3->currentIndex();
    // Clear
    _clearColor = glm::vec4((float)ui->clearColorRed->value(),
                            (float)ui->clearColorGreen->value(),
                            (float)ui->clearColorBlue->value(),
                            (float)ui->clearColorAlpha->value());
    _clearColorBuffer = ui->clearColorBuffer->isChecked();
    _clearDepth = (float)ui->clearDepthValue->value();
    _clearDepthBuffer = ui->clearDepthBuffer->isChecked();
    _clearStencil = ui->clearStencilValue->value();
    _clearStencilBuffer = ui->clearStencilBuffer->isChecked();
    // Blending
    _enableBlending = ui->enableBlending_3->isChecked();
    _rgbBlendEq = ui->rgbBlendEquation_3->currentIndex();
    _rgbSrcOp = ui->rgbSourceMode_3->currentIndex();
    _rgbDstOp = ui->rgbDestinationMode_3->currentIndex();
    _alphaBlendEq = ui->alphaBlendEquation_3->currentIndex();
    _alphaSrcOp = ui->alphaSourceMode_3->currentIndex();
    _alphaDstOp = ui->alphaDestinationMode_3->currentIndex();
    // Culling
    _enableCulling = ui->enableFaceCulling->isChecked();
    _cullingMode = ui->cullingMode->currentIndex();
    // Stencil
    _stencilMask = ui->writeStencil_3->isChecked();
    _enableStencilTest = ui->enableStencilTest_3->isChecked();
    _backFaceStencilFunc = ui->backStencilFunc->currentIndex();
    _backFaceStencilRef = ui->backStencilRef->value();
    _backFaceStencilFails = ui->backStencilTestFails->currentIndex();
    _backFaceDepthFails = ui->backDepthTestFails->currentIndex();
    _backFaceStencilPass = ui->backStencilAndDepthPass->currentIndex();
    _frontFaceStencilFunc = ui->frontStencilFunc->currentIndex();
    _frontFaceStencilRef = ui->frontStencilRef->value();
    _frontFaceStencilFails = ui->frontStencilTestFails->currentIndex();
    _frontFaceDepthFails = ui->frontDepthTestFails->currentIndex();
    _frontFaceStencilPass = ui->frontStencilAndDepthPass->currentIndex();
}

void OpenGLState::updateUiState(Ui::RenderPassUi *ui)
{
    // Color
    ui->redWrite_3->setChecked(_colorWriteMask.r);
    ui->greenWrite_3->setChecked(_colorWriteMask.g);
    ui->blueWrite_3->setChecked(_colorWriteMask.b);
    ui->alphaWrite_3->setChecked(_colorWriteMask.a);
    // Depth
    ui->enableDepthTest_3->setChecked(_depthTest);
    ui->writeDepth_3->setChecked(_depthMask);
    ui->depthFunc_3->setCurrentIndex(_depthFunc);
    // Clear
    ui->clearColorRed->setValue(_clearColor.r);
    ui->clearColorGreen->setValue(_clearColor.g);
    ui->clearColorBlue->setValue(_clearColor.b);
    ui->clearColorAlpha->setValue(_clearColor.a);
    ui->clearColorBuffer->setChecked(_clearColorBuffer);
    ui->clearDepthValue->setValue(_clearDepth);
    ui->clearDepthBuffer->setChecked(_clearDepthBuffer);
    ui->clearStencilValue->setValue(_clearStencil);
    ui->clearStencilBuffer->setChecked(_clearStencilBuffer);
    // Blending
    ui->enableBlending_3->setChecked(_enableBlending);
    ui->rgbBlendEquation_3->setCurrentIndex(_rgbBlendEq);
    ui->rgbSourceMode_3->setCurrentIndex(_rgbSrcOp);
    ui->rgbDestinationMode_3->setCurrentIndex(_rgbDstOp);
    ui->alphaBlendEquation_3->setCurrentIndex(_alphaBlendEq);
    ui->alphaSourceMode_3->setCurrentIndex(_alphaSrcOp);
    ui->alphaDestinationMode_3->setCurrentIndex(_alphaDstOp);
    // Culling
    ui->enableFaceCulling->setChecked(_enableCulling);
    ui->cullingMode->setCurrentIndex(_cullingMode);
    // Stencil
    ui->writeStencil_3->setChecked(_stencilMask);
    ui->enableStencilTest_3->setChecked(_enableStencilTest);
    ui->backStencilFunc->setCurrentIndex(_backFaceStencilFunc);
    ui->backStencilRef->setValue(_backFaceStencilRef);
    ui->backStencilTestFails->setCurrentIndex(_backFaceStencilFails);
    ui->backDepthTestFails->setCurrentIndex(_backFaceDepthFails);
    ui->backStencilAndDepthPass->setCurrentIndex(_backFaceStencilPass);
    ui->frontStencilFunc->setCurrentIndex(_frontFaceStencilFunc);
    ui->frontStencilRef->setValue(_frontFaceStencilRef);
    ui->frontStencilTestFails->setCurrentIndex(_frontFaceStencilFails);
    ui->frontDepthTestFails->setCurrentIndex(_frontFaceDepthFails);
    ui->frontStencilAndDepthPass->setCurrentIndex(_frontFaceStencilPass);
}

void OpenGLState::setOpenGLState()
{
    // Clear
    GLbitfield clearMask = 0;
    if (_clearColorBuffer)
    {
        clearMask |= GL_COLOR_BUFFER_BIT;
        GLContext::get()->glClearColor(_clearColor.r, _clearColor.g, _clearColor.b, _clearColor.a);
    }
    if (_clearDepthBuffer)
    {
        clearMask |= GL_DEPTH_BUFFER_BIT;
        GLContext::get()->glClearDepth(_clearDepth);
    }
    if (_clearStencilBuffer)
    {
        clearMask |= GL_STENCIL_BUFFER_BIT;
        GLContext::get()->glClearStencil(_clearStencil);
    }
    if (clearMask != 0)
    {
        GLContext::get()->glClear(clearMask);
    }
    // Color
    GLContext::get()->glColorMask(_colorWriteMask.r, _colorWriteMask.g, _colorWriteMask.b, _colorWriteMask.a);
    // Depth
    if (_depthTest)
    {
        GLContext::get()->glEnable(GL_DEPTH_TEST);
        GLContext::get()->glDepthFunc(getDepthStencilTest(_depthFunc));
    }
    else
    {
        GLContext::get()->glDisable(GL_DEPTH_TEST);
    }
    GLContext::get()->glDepthMask(_depthMask);
    // Blending
    if (_enableBlending)
    {
        GLContext::get()->glEnable(GL_BLEND);
        GLContext::get()->glBlendEquationSeparate(getBlendEq(_rgbBlendEq), getBlendEq(_alphaBlendEq));
        GLContext::get()->glBlendFuncSeparate(getBlendFunc(_rgbSrcOp), getBlendFunc(_rgbDstOp), getBlendFunc(_alphaSrcOp), getBlendFunc(_alphaDstOp));
    }
    else
    {
        GLContext::get()->glDisable(GL_BLEND);
    }
    // Culling
    if (_enableCulling)
    {
        GLContext::get()->glEnable(GL_CULL_FACE);
        GLContext::get()->glCullFace(getCullingMode(_cullingMode));
    }
    else
    {
        GLContext::get()->glDisable(GL_CULL_FACE);
    }
    // Stencil
    if (_enableStencilTest)
    {
        GLContext::get()->glEnable(GL_STENCIL_TEST);
        GLContext::get()->glStencilFuncSeparate(GL_BACK, getDepthStencilTest(_backFaceStencilFunc), _backFaceStencilRef, 0xFF);
        GLContext::get()->glStencilFuncSeparate(GL_FRONT, getDepthStencilTest(_frontFaceStencilFunc), _frontFaceStencilRef, 0xFF);
    }
    else
    {
        GLContext::get()->glDisable(GL_STENCIL_TEST);
    }
    if (_stencilMask)
    {
        GLContext::get()->glStencilMask(0xFF);
        GLContext::get()->glStencilOpSeparate(GL_BACK,
                                     getStencilOp(_backFaceStencilFails),
                                     getStencilOp(_backFaceDepthFails),
                                     getStencilOp(_backFaceStencilPass));
        GLContext::get()->glStencilOpSeparate(GL_FRONT,
                                     getStencilOp(_frontFaceStencilFails),
                                     getStencilOp(_frontFaceDepthFails),
                                     getStencilOp(_frontFaceStencilPass));
    }
    else
    {
        GLContext::get()->glStencilMask(0);
    }
}

GLenum OpenGLState::getDepthStencilTest(int test)
{
    static GLenum depthTestTable[] =
    {
        GL_NEVER,
        GL_LESS,
        GL_LEQUAL,
        GL_GREATER,
        GL_GEQUAL,
        GL_EQUAL,
        GL_NOTEQUAL,
        GL_ALWAYS
    };
    return (depthTestTable[test]);
}

GLenum OpenGLState::getBlendEq(int eq)
{
    static GLenum blendEqTable[] =
    {
        GL_FUNC_ADD,
        GL_FUNC_SUBTRACT,
        GL_FUNC_REVERSE_SUBTRACT
    };
    return (blendEqTable[eq]);
}

GLenum OpenGLState::getBlendFunc(int func)
{
    static GLenum blendFuncTable[] =
    {
        GL_ZERO,
        GL_ONE,
        GL_SRC_COLOR,
        GL_ONE_MINUS_SRC_COLOR,
        GL_DST_COLOR,
        GL_ONE_MINUS_DST_COLOR,
        GL_SRC_ALPHA,
        GL_ONE_MINUS_SRC_ALPHA,
        GL_DST_ALPHA,
        GL_ONE_MINUS_DST_ALPHA
    };
    return (blendFuncTable[func]);
}

GLenum OpenGLState::getCullingMode(int mode)
{
    static GLenum cullModeTable[] =
    {
        GL_FRONT,
        GL_BACK,
        GL_FRONT_AND_BACK
    };
    return (cullModeTable[mode]);
}

GLenum OpenGLState::getStencilOp(int op)
{
    static GLenum stencilOpTable[] =
    {
        GL_KEEP,
        GL_ZERO,
        GL_REPLACE,
        GL_INCR,
        GL_INCR_WRAP,
        GL_DECR,
        GL_DECR_WRAP,
        GL_INVERT
    };
    return (stencilOpTable[op]);
}
