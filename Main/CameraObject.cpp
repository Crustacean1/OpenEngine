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
void CameraControler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    {
        switch (key)
        {
        case GLFW_KEY_W:
            owner.localPosition+=glm::dquat(0,0,0,1)*camSpeed;
            //owner.localPosition += (owner.localRotation * glm::dquat(0, 0, 0, 1) * glm::conjugate(owner.localRotation)) * camSpeed;
            break;
        case GLFW_KEY_A:
            owner.localPosition+=glm::dquat(0,-1,0,0)*camSpeed;
            //owner.localPosition += (owner.localRotation * glm::dquat(0, -1, 0, 0) * glm::conjugate(owner.localRotation)) * camSpeed;
            break;
        case GLFW_KEY_D:
            owner.localPosition+=glm::dquat(0,1,0,0)*camSpeed;
            //owner.localPosition += (owner.localRotation * glm::dquat(0, 1, 0, 0) * glm::conjugate(owner.localRotation)) * camSpeed;
            break;
        case GLFW_KEY_S:
            owner.localPosition+=glm::dquat(0,0,0,-1)*camSpeed;
            //owner.localPosition += (owner.localRotation * glm::dquat(0, 0, 0, -1) * glm::conjugate(owner.localRotation)) * camSpeed;
            break;
        default:
            break;
        }
        //owner.flushTransform();
    }
}