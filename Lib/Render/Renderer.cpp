#include "Renderer.h"
#include "Render.h"
#include "../Shader/Shader.h"


OpenEngine::Shader * OpenEngine::Renderer::getShader()
{
    return myShader;
}
void OpenEngine::Renderer::setShader(Shader * _shader)
{
    myShader = _shader;
}