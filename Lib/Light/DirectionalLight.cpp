#include "DirectionalLight.h"
#include "../Shader/Shader.h"
#include <iostream>
void OpenEngine::DirectionalLight::update()
{
    shader->set(getName()+(std::string)".isActiev",Light::active);
    shader->set(getName()+(std::string)".dir",lastViewDirection);
    shader->set(getName()+(std::string)".color",color);
    shader->set(getName()+(std::string)".ambient",ambient);
    shader->set(getName()+(std::string)".diffuse",diffuse);
    shader->set(getName()+(std::string)".specular",specular);
}
void OpenEngine::DirectionalLight::illuminate(const glm::mat4 & mat)
{
    glm::vec4 lPos = mat*glm::vec4(0,0,-1,0);
    lastViewDirection = glm::vec3(lPos.x,lPos.y,lPos.z);
    update();
}