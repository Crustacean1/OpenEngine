#include "Physical.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <iostream>

OpenEngine::Physical::Physical(Object *_obj,double _ad, double _vd) : Component(_obj), velocity(glm::vec3(0, 0, 0)), acceleration(glm::vec3(0, 0, 0)), angularMomentum(glm::vec3(0, 0, 0)), powerMomentum(glm::vec3(0, 0, 0)),angDamp(_ad),velDamp(_vd) {}

void OpenEngine::Physical::update(double delta)
{
    glm::vec3 buff = (float)delta * velocity + (float)(delta * delta * 0.5) * acceleration;
    object->localPosition += glm::dquat(0, buff.x, buff.y, buff.z);
    //std::cout<<acceleration.x<<" "<<acceleration.y<<" "<<acceleration.z<<std::endl;
    velocity += (float)delta * acceleration;
    glm::vec3 ax = glm::vec3(angularMomentum.x + powerMomentum.x * delta * 0.5,
                             angularMomentum.y + powerMomentum.y * delta * 0.5,
                             angularMomentum.z + powerMomentum.z * delta * 0.5);

    acceleration = glm::vec3(0, 0, 0);

    float angle = glm::length(ax);
    if (angle != 0)
    {
        ax = ax / angle;
    }
    object->localRotation *= glm::dquat(cos(angle * delta * 0.5), (float)sin(angle * delta * 0.5) * glm::vec3(ax));
    angularMomentum += powerMomentum * (float)delta;

    object->flushTransform();
    //std::cout<<powerMomentum.x<<" "<<powerMomentum.y<<" "<<powerMomentum.z<<std::endl;
    powerMomentum = glm::vec3(0, 0, 0);
    velocity = velocity*(float)pow(velDamp,delta);
    angularMomentum = angularMomentum*(float)pow(angDamp,delta);
}