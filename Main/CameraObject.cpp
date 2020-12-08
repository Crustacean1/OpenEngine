#include "CameraObject.h"
#include "../Lib/Window/Window.h"
#include <GLFW/glfw3.h>
#include "../Lib/Physics/Physical.h"
#include "../Lib/Physics/Physics.h"

void CameraControler::init()
{
    glfwGetCursorPos(OpenEngine::Window::getMainWindow(), &prevX, &prevY);
}
void CameraControler::mouseMovementCallback(GLFWwindow *window, double xpos, double ypos)
{
    //glm::dquat ax = owner.localRotation * glm::dquat(0, 0, 1, 0) * glm::conjugate(owner.localRotation);
    double dx = -(xpos - prevX);
    double dy = (ypos - prevY);

    prevX = xpos;
    prevY = ypos;

    object.transform.localRotation = glm::angleAxis((float)(xpos*xfactor),glm::vec3(0,1,0))*glm::angleAxis((float)(ypos*yfactor),glm::vec3(1,0,0));

}
void CameraControler::update(double delta)
{
    GLFWwindow *window = OpenEngine::Window::getMainWindow();

    float coeff = (1 + (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) * 2.5);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
    {
        object.transform.localPosition += object.transform.transformVector(glm::vec3(0,0,1))*camSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
    {
        object.transform.localPosition += object.transform.transformVector(glm::vec3(1,0,0))*camSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
    {
        object.transform.localPosition += object.transform.transformVector(glm::vec3(0,0,-1))*camSpeed;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
    {
        object.transform.localPosition += object.transform.transformVector(glm::vec3(-1,0,0))*camSpeed;
    }

    object.transform.flushTransform();
}