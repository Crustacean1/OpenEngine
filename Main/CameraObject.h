#ifndef CAMERAOBJECT
#define CAMERAOBJECT

#include "../Lib/Object/Object.h"
#include "../Lib/Camera/Camera.h"
#include "../Lib/Input/Input.h"
#include "../Lib/Component/Behaviour/Behaviour.h"
#include "../Lib/Component/Behaviour/BehaviourManager.h"
#include <iostream>

class CameraControler : public OpenEngine::Behaviour, public OpenEngine::MouseMovementInput, public OpenEngine::MouseScrollInput
{
    double prevX;
    double prevY;

    double spos = 1;

public:
    double xfactor = -0.001;
    double yfactor = -0.001;

    double sfactor = 0.01;

    double camSpeed = -0.5;

    CameraControler(OpenEngine::Object &obj) : Behaviour(obj) {}
    void mouseMovementCallback(GLFWwindow *window, double xpos, double ypos);
    void mouseScrollCallback(GLFWwindow * window,double x,double y);
    void update(double delta) override;
    void init() override;
    BaseComponent* instantiate(){return new CameraControler(*this);}
};

#endif /*CAMERAOBJECT*/