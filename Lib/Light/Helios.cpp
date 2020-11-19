#include "Helios.h"
#include "../Light/Light.h"
#include "../Camera/Camera.h"

void OpenEngine::Helios::illuminate(Camera * cam)
{
    glm::vec4 lPos;
    for(auto & component : components)
    {
        component->illuminate(cam->getViewMatrix(component->object.getGlobalPosition(),
                                  component->object.getGlobalRotation(),
                                  component->object.getGlobalScale()));
    }
}