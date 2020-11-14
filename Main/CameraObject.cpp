#include "CameraObject.h"
#include "../Lib/Window/Window.h"
#include <GLFW/glfw3.h>

/*
void CameraObject::init()
{
    camera = std::shared_ptr<OpenEngine::Camera>(new OpenEngine::Camera(this));
    controler = std::shared_ptr<CameraControler>(new CameraControler(*this));
    setLocalPosition(glm::vec3(0, 0, -2));
}*/
void CameraControler::init()
{
    glfwGetCursorPos(OpenEngine::Window::getMainWindow(),&prevX,&prevY);
}
void CameraControler::mouseMovementCallback(GLFWwindow *window, double xpos, double ypos)
{
    //glm::dquat ax = owner.localRotation * glm::dquat(0, 0, 1, 0) * glm::conjugate(owner.localRotation);
    xpos = (xpos-prevX)+ (3*3.141592/4)/xfactor;
    ypos = (ypos-prevY) + (3.141592/4)/yfactor;
    owner.setLocalRotation(glm::angleAxis((float)(xpos * xfactor), glm::vec3(0, -1, 0)) * glm::angleAxis((float)(ypos * yfactor), glm::vec3(1, 0, 0)));

    /*auto yAxis = (owner.localRotation * glm::dquat(0,0,1,0) * glm::conjugate(owner.localRotation));
    auto xAxis = (owner.localRotation * glm::dquat(0,1,0,0) * glm::conjugate(owner.localRotation));

    owner.localRotation = ((glm::dquat) glm::angleAxis((float)((xpos-prevX)*-0.001),glm::vec3(yAxis.x,yAxis.y,yAxis.z))* 
    (glm::dquat) glm::angleAxis((float)((ypos-prevY)*-0.001),glm::vec3(xAxis.x,xAxis.y,xAxis.z)) * owner.localRotation);

    prevX = xpos;
    prevY = ypos;*/
}
void CameraControler::update(double delta)
{
    GLFWwindow *window = OpenEngine::Window::getMainWindow();

    delta = delta * (1 + (glfwGetKey(window, GLFW_KEY_LEFT_ALT)) * 1.5);
    
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
    //std::cout<<owner.localPosition.x<<" "<<owner.localPosition.y<<" "<<owner.localPosition.z<<std::endl;

    owner.flushTransform();
}