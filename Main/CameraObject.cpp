#include "CameraObject.h"
#include <GLFW/glfw3.h>

void CameraObject::init()
{
    camera = std::shared_ptr<OpenEngine::Camera>(new OpenEngine::Camera(this));
    controler = std::shared_ptr<CameraControler>(new CameraControler(*this));
    setLocalPosition(glm::vec3(0, 0, -2));
}
void CameraControler::mouseMovementCallback(GLFWwindow *window, double xpos, double ypos)
{
    owner.setLocalRotation(glm::angleAxis((float)(xpos * xfactor), glm::vec3(0, 1, 0)) * glm::angleAxis((float)(ypos * yfactor), glm::vec3(1, 0, 0)));
}