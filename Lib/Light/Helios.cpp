#include "Helios.h"
#include "../Light/Light.h"
#include "../Camera/Camera.h"
#include "../Component/Transform/Transform.h"
#include "../Object/Object.h"
//#include <iostream>
void OpenEngine::Helios::illuminate(Camera * cam)
{
    glm::vec4 lPos;
    for(auto & component : components)
    {
        component->illuminate(cam->getViewMatrix(component->object.transform.getGlobalPosition(),
                                  component->object.transform.getGlobalRotation(),
                                  component->object.transform.getGlobalScale()));
    }
}