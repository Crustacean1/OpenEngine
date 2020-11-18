#include "PointLight.h"
#include "../Shader/Shader.h"

void OpenEngine::PointLight::update()
{
    shader->set(basename+(std::string)".active",active);
    shader->set(basename+(std::string)".pos",position);
    shader->set(basename+(std::string)".color",color);
}