#include "Render.h"
#include "Renderer.h"
#include "../Shader/Shader.h"

void OpenEngine::Render::addRenderer(Renderer *_renderer)
{
    if(_renderer->getShader().get()==nullptr){return;}
    renderers[_renderer->getShader().get()].insert(_renderer);
}
void OpenEngine::Render::dropRenderer(Renderer *_renderer)
{
    auto shID = _renderer->getShader().get();
    renderers[shID].erase(renderers[shID].find(_renderer));
}
OpenEngine::Renderer::~Renderer()
{
    if (myRender != nullptr)
    {
        myRender->dropRenderer(this);
    }
}