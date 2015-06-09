#include "RenderPass.hh"

#include <QOpenGLTexture>

RenderPass::RenderPass() :
        _fbo(0),
        _vertex(NULL),
        _fragment(NULL),
        _program(NULL),
        _previous(NULL)
{
}

RenderPass::~RenderPass()
{

}

void RenderPass::setVertexCode(QString code)
{
    _vertexCode = code;
}

void RenderPass::setFragmentCode(QString code)
{
    _fragmentCode = code;
}
