#include "Camera.h"
#include "../Object/Object.h"

OpenEngine::Camera::Camera(Object * object,double _fov,double _aspect,double _n,double _f) : owner(object),
                            projMat(* new glm::mat4(1.f)),fov(_fov),aspect(_aspect),near(_n),far(_f){computeProjectionMatrix();}

glm::mat4 OpenEngine::Camera::getMatrix(glm::dquat _position)
{
    glm::dquat view = glm::inverse(owner->getGlobalRotation());
    glm::mat4 a = glm::mat4(1.f);
    glm::mat4 b =(glm::mat4_cast(view));
    //a = glm::mat4(1.f);
    a = glm::translate(a,-glm::vec3(owner->getGlobalPosition().x,owner->getGlobalPosition().y,owner->getGlobalPosition().z));


    a = b*a;

    a = glm::scale(a,glm::vec3(owner->getGlobalScale().x,owner->getGlobalScale().y,owner->getGlobalScale().z));
    //a= glm::mat4(1.f);
    return projMat*b;
}

void OpenEngine::Camera::computeProjectionMatrix()
{
    projMat = glm::perspective(glm::radians(fov),aspect,near,far);
}