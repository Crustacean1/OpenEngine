#include "PointLight.h"
#include "../Shader/Shader.h"

void OpenEngine::PointLight::update()
{
    shader->set(basename+(std::string)".active",active);
    shader->set(basename+(std::string)".pos",lastViewPosition);
    shader->set(basename+(std::string)".color",color);
}
void OpenEngine::PointLight::illuminate(const glm::mat4 & mat)
{
    if(active&&shader!=nullptr&&getBinding()>=0)
    {
        glm::vec4 lPos = glm::vec4(0,0,0,0)*mat;
        lastViewPosition = glm::vec3(lPos.x,lPos.y,lPos.z);
        update();
    }
}