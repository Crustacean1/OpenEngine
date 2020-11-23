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

    CameraControler(OpenEngine::Object &obj) : owner(obj), Behaviour(obj) {}
    void mouseMovementCallback(GLFWwindow *window, double xpos, double ypos);
    void update(double delta) override;
    void init() override;
};


#endif /*CAMERAOBJECT*/