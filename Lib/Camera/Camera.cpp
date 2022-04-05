#include "Camera.h"
#include "../Object/Object.h"

OpenEngine::BasicCamera::BasicCamera(Object &_obj, double _fov, double _aspect, double _n, double _f) : Camera(_obj), projMat(*new glm::mat4(1.f)), fov(_fov), aspect(_aspect), near(_n), far(_f)
{
    computeProjectionMatrix();
}

glm::mat4 OpenEngine::BasicCamera::getViewMatrix(glm::vec3 _position, glm::dquat _rotation, glm::vec3 _scale)
{
    //glm::dquat view = glm::inverse(owner->getGlobalRotation());
    glm::mat4 a = glm::mat4(1.f);

    //Object transforms
    glm::vec3 scale = object.transform.getGlobalScale();
    //scale /=(scale.x*scale.x+scale.y*scale.y+scale.z*scale.z);
    
    a = glm::scale(a,_scale);
    a = (glm::mat4)glm::mat4_cast(_rotation) * a;
    a = glm::translate(glm::mat4(1.f), (_position - object.transform.getGlobalPosition())) * a;

    //Camera transforms, can be buffered per frame
    a = (glm::mat4)glm::mat4_cast(glm::inverse(object.transform.getGlobalRotation())) * a;
    //a = glm::scale(a, scale);


    //a = glm::scale(a,scale);

    //a= glm::mat4(1.f);
    return a;
}


OpenEngine::Camera::Camera(OpenEngine::Object &_obj) : OpenEngine::BaseComponent(_obj) {}

void OpenEngine::BasicCamera::computeProjectionMatrix()
{
    projMat = glm::perspective(glm::radians(fov), aspect, near, far);
}

OpenEngine::BaseComponent* OpenEngine::BasicCamera::instantiate()
{
    return new BasicCamera(object,fov,aspect,near,far);
}