#include "Object.h"

std::string OpenEngine::Object::mainIndex = "\0";

std::string OpenEngine::Object::incrementIndex(std::string &index)
{
    unsigned int sum = 1;
    for (unsigned int i = 0; i < index.size() && sum != 0; i++)
    {
        sum += index[i];
        index[i] = sum & 255;
        sum = sum >> 8;
    }
    if (sum)
    {
        index += (char)0;
    }
    return index;
}

OpenEngine::Object::Object(std::shared_ptr<Object> _parent) : parent(_parent)
{
    localRotation = globalRotation = glm::dquat(1, 0, 0, 0);
    localScale = globalScale = glm::dquat(0, 1, 1, 1);
    localPosition = globalPosition = glm::dquat(0, 0, 0, 0);
    flushTransform();
}
std::string OpenEngine::Object::getId() const
{
    return index;
}

// Global getters

glm::dquat OpenEngine::Object::getGlobalPosition()
{
    return globalRotation * localRotation * (globalPosition + localPosition) * glm::conjugate(localRotation) * glm::conjugate(globalRotation);
}
glm::dquat OpenEngine::Object::getGlobalRotation()
{
    return globalRotation * localRotation;
}
glm::dquat OpenEngine::Object::getGlobalScale()
{
    return glm::dquat(globalScale.w * localScale.w,
                      globalScale.x * localScale.x,
                      globalScale.y * localScale.y,
                      globalScale.z * localScale.z);
}

// Local getters

glm::dquat OpenEngine::Object::getLocalPosition()
{
    return localPosition;
}
glm::dquat OpenEngine::Object::getLocalRotation()
{
    return localRotation;
}
glm::dquat OpenEngine::Object::getLocalScale()
{
    return localScale;
}

//Local setters

void OpenEngine::Object::setLocalPosition(glm::vec3 _pos)
{
    localPosition = glm::quat(0, _pos);
    flushTransform();
}
void OpenEngine::Object::setLocalRotation(glm::dquat _rotation)
{
    localRotation = _rotation;
    
    flushTransform();
}
void OpenEngine::Object::setLocalScale(glm::vec3 _scale)
{
    localScale = glm::dquat(0, _scale);

    flushTransform();
}

//Global setter

void OpenEngine::Object::setGlobalScale(glm::vec3 _scale)
{
    localScale = glm::dquat(
        0,
        _scale.x / globalScale.x,
        _scale.y / globalScale.y,
        _scale.z / globalScale.z);
    if (parent.lock() == nullptr)
    {
        globalScale = localScale;
    }
    flushTransform();
}
void OpenEngine::Object::setGlobalRotation(glm::dquat _rotation)
{
    localRotation = glm::inverse(globalRotation) * _rotation;
    flushTransform();
}
void OpenEngine::Object::setGlobalPosition(glm::vec3 _pos)
{
    localPosition = glm::inverse(localRotation) * glm::dquat(0, (_pos.x - globalPosition.x) / localScale.x, (_pos.y - globalPosition.y) / localScale.y, (_pos.z - globalPosition.z) / localScale.z) * glm::inverse(glm::conjugate(localRotation));
    flushTransform();
}

void OpenEngine::Object::flushTransform()
{
    if (parent.lock().get() != nullptr)
    {
        std::shared_ptr<Object> _parent = parent.lock();
        glm::dquat _pos, _scale, _rot;
        _scale = glm::dquat(_parent->globalScale.x * _parent->localScale.x,
                            _parent->globalScale.y * _parent->localScale.y,
                            _parent->globalScale.z * _parent->localScale.z,
                            _parent->globalScale.w * _parent->localScale.w);
        _rot = _parent->globalRotation * _parent->localRotation;
        _pos = glm::dquat(_parent->globalScale.x * _parent->localPosition.x,
                          _parent->globalScale.y * _parent->localPosition.y,
                          _parent->globalScale.z * _parent->localPosition.z,
                          _parent->globalScale.w * _parent->localPosition.w);
        _pos = _parent->globalRotation * _pos * glm::conjugate(_parent->globalRotation);
        _pos += _parent->globalPosition;
    }
    for (const auto &child : children)
    {
        child.second->flushTransform();
    }
}