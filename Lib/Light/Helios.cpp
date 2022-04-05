#include "Helios.h"
#include "../Light/Light.h"
#include "../Camera/Camera.h"
#include "../Component/Transform/Transform.h"
#include "../Object/Object.h"

//unsigned int OpenEngine::Helios::mainIndex = 0;
std::map<unsigned int,OpenEngine::Helios *> OpenEngine::Helios::managers;

void OpenEngine::Helios::illuminate(Camera *cam)
{
    glm::vec4 lPos;
    for (auto &component : components)
    {
        component->illuminate(cam->getViewMatrix(component->object.transform.getGlobalPosition(),
                                                 component->object.transform.getGlobalRotation(),
                                                 component->object.transform.getGlobalScale()));
    }
}