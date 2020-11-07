#include "Camera.h"
#include "../Object/Object.h"

OpenEngine::Camera::Camera(Object * object,double _fov,double _aspect,double _n,double _f) : owner(object),
                            projMat(* new glm::mat4(1.f)),fov(_fov),aspect(_aspect),near(_n),far(_f){computeProjectionMatrix();}

glm::mat4 OpenEngine::Camera::getMatrix(glm::vec3 _position,glm::dquat _rotation,glm::vec3 _scale)// invalid parameters TODO
{
    //glm::dquat view = glm::inverse(owner->getGlobalRotation());
    glm::mat4 a = glm::mat4(1.f);

    //Object transforms
    a = glm::scale(a,_scale);
    a = (glm::mat4)glm::mat4_cast(_rotation)*a;
    a = glm::translate(a,_position);

    //Camera transforms, can be buffererd per frame
    a = glm::translate(a,-owner->getGlobalPosition());
    a = a*(glm::mat4)glm::mat4_cast(glm::inverse(owner->getGlobalRotation()));

    //a= glm::mat4(1.f);
    return projMat*a;
}

void OpenEngine::Camera::computeProjectionMatrix()
{
    projMat = glm::perspective(glm::radians(fov),aspect,near,far);
}