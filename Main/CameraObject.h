#ifndef CAMERAOBJECT
#define CAMERAOBJECT

#include "../Lib/Object/Object.h"
#include "../Lib/Camera/Camera.h"
#include "../Lib/Input/Input.h"
#include <iostream>

class CameraControler : public OpenEngine::MouseMovementInput, public OpenEngine::KeyInput
{
    OpenEngine::Object & owner;
public:

    double xfactor = 0.002;
    double yfactor = -0.002;

    double camSpeed = 2;

    CameraControler(OpenEngine::Object & obj): owner(obj){}
    void mouseMovementCallback(GLFWwindow *window, double xpos, double ypos);
    void keyCallback(GLFWwindow * window,double delta);
};

class CameraObject : public OpenEngine::Object
{
    std::shared_ptr<OpenEngine::Camera> camera;
    std::shared_ptr<CameraControler> controler;

public:
    CameraObject(std::shared_ptr<OpenEngine::Object> obj) : OpenEngine::Object::Object(obj) {}
    void init();
    std::shared_ptr<OpenEngine::Camera> getCamera() { return camera; }
    std::shared_ptr<CameraControler> getControler(){return controler;}
    ~CameraObject() { std::cout << "I'm suffering"; }
};

#endif /*CAMERAOBJECT*/