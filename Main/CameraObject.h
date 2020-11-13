#ifndef CAMERAOBJECT
#define CAMERAOBJECT

#include "../Lib/Object/Object.h"
#include "../Lib/Camera/Camera.h"
#include "../Lib/Input/Input.h"
#include "../Lib/Component/Behaviour.h"
#include "../Lib/Component/BehaviourManager.h"
#include <iostream>

class CameraControler : public OpenEngine::Behaviour, public OpenEngine::MouseMovementInput
{
    OpenEngine::Object &owner;
    double prevX;
    double prevY;

public:
    double xfactor = 0.002;
    double yfactor = -0.002;

    double camSpeed = 2;

    CameraControler(OpenEngine::Object &obj,OpenEngine::BehaviourManager * manager = nullptr) : owner(obj), Behaviour(obj,manager) {}
    void mouseMovementCallback(GLFWwindow *window, double xpos, double ypos);
    void update(double delta) override;
    void init() override;
};

/*
class CameraObject : public OpenEngine::Object
{
    std::shared_ptr<OpenEngine::Camera> camera;
    std::shared_ptr<CameraControler> controler;

public:
    CameraObject() : OpenEngine::Object::Object() {}
    void init();
    std::shared_ptr<OpenEngine::Camera> getCamera() { return camera; }
    std::shared_ptr<CameraControler> getControler(){return controler;}
    ~CameraObject() {}
};*/

#endif /*CAMERAOBJECT*/