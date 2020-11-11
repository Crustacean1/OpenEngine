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
    glm::dquat ax = owner.localRotation * glm::dquat(0,0,1,0) * glm::conjugate(owner.localRotation);
    owner.setLocalRotation(glm::angleAxis((float)(xpos * xfactor), glm::vec3(0,1,0)) * glm::angleAxis((float)(ypos * yfactor), glm::vec3(1, 0, 0)));
}
void CameraControler::keyCallback(GLFWwindow *window, double delta)
{
    delta = delta*(1+(glfwGetKey(window,GLFW_KEY_LEFT_ALT))*1.5);
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        owner.localPosition += (owner.localRotation * glm::dquat(0, 0, 0, -1) * glm::conjugate(owner.localRotation)) * camSpeed * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        owner.localPosition += (owner.localRotation * glm::dquat(0, -1, 0, 0) * glm::conjugate(owner.localRotation)) * camSpeed * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        owner.localPosition += (owner.localRotation * glm::dquat(0, 0, 0, 1) * glm::conjugate(owner.localRotation)) * camSpeed * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        owner.localPosition += (owner.localRotation * glm::dquat(0, 1, 0, 0) * glm::conjugate(owner.localRotation)) * camSpeed * delta;
    }

    owner.flushTransform();
}