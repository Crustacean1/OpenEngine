#include "PointLight.h"
#include "../Shader/Shader.h"

void OpenEngine::PointLight::update()
{
    shader->set(getName()+(std::string)".active",active);
    shader->set(getName()+(std::string)".pos",lastViewPosition);
    shader->set(getName()+(std::string)".color",color);
    shader->set(getName()+(std::string)".ambient",ambient);
    shader->set(getName()+(std::string)".diffuse",diffuse);
    shader->set(getName()+(std::string)".specular",specular);
}
void OpenEngine::PointLight::illuminate(const glm::mat4 & mat)
{
    if(active&&shader!=nullptr&&getBinding()>=0)
    {
        glm::vec4 lPos = mat*glm::vec4(0,0,0,1);
        lastViewPosition = glm::vec3(lPos.x,lPos.y,lPos.z);
        update();
    }
}