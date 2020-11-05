#include "Renderer.h"
#include "Render.h"
#include "../Shader/Shader.h"

void OpenEngine::Renderer::setRender(std::shared_ptr<Render> _render)
{
    if(myRender!=nullptr)
    {
        myRender->dropRenderer(this);
    }
    myRender = _render;
    myRender->addRenderer(this);
}
std::shared_ptr<OpenEngine::Shader> OpenEngine::Renderer::getShader()
{
    return myShader;
}
void OpenEngine::Renderer::setShader(std::shared_ptr<Shader> _shader)
{
    myShader = _shader;
}