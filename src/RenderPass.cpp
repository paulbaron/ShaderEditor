#include "RenderPass.hh"

RenderPass::RenderPass() :
        _fbo(new QOpenGLFramebufferObject(1280, 720)),
        _vertex(NULL),
        _fragment(NULL),
        _program(NULL),
        _previous(NULL)
{
}

RenderPass::~RenderPass()
{

}

