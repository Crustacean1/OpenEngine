#include "Transform.h"
#include "../../Object/Object.h"
// Global getters

OpenEngine::Transform::Transform(Object &_obj) : BaseComponent(_obj) {}

glm::vec3 OpenEngine::Transform::getGlobalPosition()
{
    auto res = globalPosition +
               (globalRotation *
                glm::dquat(localPosition.w * globalScale.w, localPosition.x * globalScale.x, localPosition.y * globalScale.y, localPosition.z * globalScale.z) *
                glm::conjugate(globalRotation));
    return glm::vec3(res.x, res.y, res.z);
}
glm::dquat OpenEngine::Transform::getGlobalRotation()
{
    return globalRotation * localRotation;
}
glm::vec3 OpenEngine::Transform::getGlobalScale()
{
    return glm::vec3(globalScale.x * localScale.x,
                     globalScale.y * localScale.y,
                     globalScale.z * localScale.z);
}

//Global setter

void OpenEngine::Transform::setGlobalScale(glm::vec3 _scale)
{
    localScale = glm::dquat(
        0,
        _scale.x / globalScale.x,
        _scale.y / globalScale.y,
        _scale.z / globalScale.z);
    flushTransform();
}
void OpenEngine::Transform::setGlobalRotation(glm::dquat _rotation)
{
    localRotation = glm::inverse(globalRotation) * _rotation;
    flushTransform();
}
void OpenEngine::Transform::setGlobalPosition(glm::vec3 _pos)
{
    localPosition = glm::inverse(localRotation) * glm::dquat(0, (_pos.x - globalPosition.x) / localScale.x, (_pos.y - globalPosition.y) / localScale.y, (_pos.z - globalPosition.z) / localScale.z) * glm::inverse(glm::conjugate(localRotation));
    flushTransform();
}

void OpenEngine::Transform::flushTransform()
{
    if (object.getParent() != nullptr)
    {
        Transform parent = object.getParent()->transform;
        glm::dquat _pos, _scale, _rot;
        _scale = glm::dquat(parent.globalScale.w * parent.localScale.w,
                            parent.globalScale.x * parent.localScale.x,
                            parent.globalScale.y * parent.localScale.y,
                            parent.globalScale.z * parent.localScale.z);
        _rot = parent.globalRotation * parent.localRotation;
        _pos = glm::dquat(parent.globalScale.w * parent.localPosition.w,
                          parent.globalScale.x * parent.localPosition.x,
                          parent.globalScale.y * parent.localPosition.y,
                          parent.globalScale.z * parent.localPosition.z);
        _pos = parent.globalRotation * _pos * glm::conjugate(parent.globalRotation);
        _pos += parent.globalPosition;
        globalPosition = _pos;
        globalRotation = _rot;
        globalScale = _scale;
    }
    for (const auto &child : object.getChildren())
    {
        child->transform.flushTransform();
    }
}

glm::dquat OpenEngine::Transform::transformVector(glm::vec3 vec)
{
    glm::dquat temp(0, vec.x * localScale.x, vec.y * localScale.y, vec.z * localScale.z);
    temp = localRotation * temp * glm::conjugate(localRotation);
    temp = glm::dquat(temp.w * globalScale.w, temp.x * globalScale.x, temp.y * globalScale.y, temp.z * globalScale.z);
    temp = globalRotation * temp * glm::conjugate(globalRotation);
    return temp;
}
glm::dquat OpenEngine::Transform::transformPosition(glm::vec3 vec)
{
    glm::dquat temp(0, vec.x * localScale.x, vec.y * localScale.y, vec.z * localScale.z);
    temp = localPosition + localRotation * temp * glm::conjugate(localRotation);
    temp = glm::dquat(temp.w * globalScale.w, temp.x * globalScale.x, temp.y * globalScale.y, temp.z * globalScale.z);
    temp = globalPosition + globalRotation * temp * glm::conjugate(globalRotation);
    return temp;
}