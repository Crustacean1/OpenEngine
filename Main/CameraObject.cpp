#include "CameraObject.h"

void CameraObject::init()
{
    camera = std::shared_ptr<OpenEngine::Camera>(new OpenEngine::Camera(this));
    setLocalPosition(glm::vec3(0,0,-2));
}