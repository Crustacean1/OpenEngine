#ifndef CAMERAOBJECT
#define CAMERAOBJECT

#include "../Lib/Object/Object.h"
#include "../Lib/Camera/Camera.h"
#include <iostream>


class CameraObject : public OpenEngine::Object
{
    std::shared_ptr<OpenEngine::Camera> camera;
    public:
    CameraObject(std::shared_ptr<OpenEngine::Object> obj) : OpenEngine::Object::Object(obj){}
    void init();
    std::shared_ptr<OpenEngine::Camera> getCamera(){return camera;}
    ~CameraObject(){std::cout<<"I'm suffering";}
};

#endif /*CAMERAOBJECT*/