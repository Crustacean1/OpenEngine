#include "Render.h"
#include "Renderer.h"
#include "../Shader/Shader.h"

void OpenEngine::Render::add(Renderer *_renderer)
{
    if(_renderer->getShader()==nullptr){return;}
    renderers[_renderer->getShader()].insert(_renderer);
}
void OpenEngine::Render::drop(Renderer *_renderer)
{
    auto shID = _renderer->getShader();
    renderers[shID].erase(renderers[shID].find(_renderer));
}