#include "CameraObject.h"
#include "../Lib/Window/Window.h"
#include <GLFW/glfw3.h>
#include "../Lib/Physics/Physical.h"

void CameraControler::init()
{
    glfwGetCursorPos(OpenEngine::Window::getMainWindow(), &prevX, &prevY);
}
void CameraControler::mouseMovementCallback(GLFWwindow *window, double xpos, double ypos)
{
    //glm::dquat ax = owner.localRotation * glm::dquat(0, 0, 1, 0) * glm::conjugate(owner.localRotation);
    double dx = (xpos - prevX);
    double dy = -(ypos - prevY);

    prevX = xpos;
    prevY = ypos;
    //std::cout<<xpos<<" "<<ypos<<std::endl;
    //object->setLocalRotation(glm::angleAxis((float)(xpos * xfactor), glm::vec3(0, -1, 0)) * glm::angleAxis((float)(ypos * yfactor), glm::vec3(1, 0, 0)));
    auto physical = object->getParent()->getComponent<OpenEngine::Physical>(0);
    if (physical == nullptr)
    {
        return;
    }

    physical->actMomentum(glm::vec3(0, -0.1 * dx, 0));
    physical->actMomentum(glm::vec3(-0.1 * dy, 0, 0));
}
void CameraControler::update(double delta)
{
    GLFWwindow *window = OpenEngine::Window::getMainWindow();

    float coeff = (1 + (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) * 4.5);

    auto phys = object->getParent()->getComponent<OpenEngine::Physical>(0);
    if (phys == nullptr)
    {
        return;
    }
    glm::dquat force = glm::dquat(0, 0, 0, 0);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        force += (object->getParent()->localRotation * glm::dquat(0, 0, 0, -1) * glm::conjugate(object->getParent()->localRotation )) * camSpeed;
        //object->getParent()->localPosition += (object->localRotation * glm::dquat(0, 0, 0, 1) * glm::conjugate(object->localRotation)) * camSpeed * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        force += (object->getParent()->localRotation * glm::dquat(0, -1, 0, 0) * glm::conjugate(object->getParent()->localRotation )) * camSpeed;
        //object->getParent()->localPosition += (object->localRotation * glm::dquat(0, 1, 0, 0) * glm::conjugate(object->localRotation)) * camSpeed * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        force += (object->getParent()->localRotation * glm::dquat(0, 0, 0, 1) * glm::conjugate(object->getParent()->localRotation )) * camSpeed;
        //object->getParent()->localPosition += (object->localRotation * glm::dquat(0, 0, 0, -1) * glm::conjugate(object->localRotation)) * camSpeed * delta;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        force += (object->getParent()->localRotation * glm::dquat(0, 1, 0, 0) * glm::conjugate(object->getParent()->localRotation )) * camSpeed;
        //object->getParent()->localPosition += (object->localRotation * glm::dquat(0, -1, 0, 0) * glm::conjugate(object->localRotation)) * camSpeed * delta;
    }
    //std::cout<<"set"<<std::endl;
    //std::cout<<force.x<<" "<<force.y<<" "<<force.z<<"\n";
    phys->actForce(glm::vec3(force.x, force.y, force.z)*coeff);
    //std::cout<<owner.localPosition.x<<" "<<owner.localPosition.y<<" "<<owner.localPosition.z<<std::endl;

    object->getParent()->flushTransform();
}