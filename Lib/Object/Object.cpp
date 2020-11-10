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

OpenEngine::Object::Object(Object * _parent) : parent(_parent)
{
    localRotation = globalRotation = glm::dquat(1, 0, 0, 0);
    localScale = globalScale = glm::dquat(0, 1, 1, 1);
    localPosition = globalPosition = glm::dquat(0, 0, 0, 0);
    if (_parent != nullptr)
    {
        globalPosition = glm::dquat(0, _parent->getGlobalPosition());
        globalRotation = _parent->getGlobalRotation();
        globalScale = glm::dquat(0, _parent->getGlobalScale());
        _parent->children[getId()] = this;
    }
    flushTransform();
}
std::string OpenEngine::Object::getId() const
{
    return index;
}

// Global getters

glm::vec3 OpenEngine::Object::getGlobalPosition()
{
    auto res = globalPosition +
               (globalRotation *
                glm::dquat(localPosition.w * globalScale.w, localPosition.x * globalScale.x, localPosition.y * globalScale.y, localPosition.z * globalScale.z) * glm::conjugate(globalRotation));
    return glm::vec3(res.x, res.y, res.z);
}
glm::dquat OpenEngine::Object::getGlobalRotation()
{
    return globalRotation * localRotation;
}
glm::vec3 OpenEngine::Object::getGlobalScale()
{
    return glm::vec3(globalScale.x * localScale.x,
                     globalScale.y * localScale.y,
                     globalScale.z * localScale.z);
}

// Local getters

glm::vec3 OpenEngine::Object::getLocalPosition()
{
    return glm::vec3(localPosition.x, localPosition.y, localPosition.z);
}
glm::dquat OpenEngine::Object::getLocalRotation()
{
    return localRotation;
}
glm::vec3 OpenEngine::Object::getLocalScale()
{
    return glm::vec3(localScale.x, localScale.y, localScale.z);
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
    if (parent == nullptr)
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
    if (parent != nullptr)
    {
        glm::dquat _pos, _scale, _rot;
        _scale = glm::dquat(parent->globalScale.x * parent->localScale.x,
                            parent->globalScale.y * parent->localScale.y,
                            parent->globalScale.z * parent->localScale.z,
                            parent->globalScale.w * parent->localScale.w);
        _rot = parent->globalRotation * parent->localRotation;
        _pos = glm::dquat(parent->globalScale.x * parent->localPosition.x,
                          parent->globalScale.y * parent->localPosition.y,
                          parent->globalScale.z * parent->localPosition.z,
                          parent->globalScale.w * parent->localPosition.w);
        _pos = parent->globalRotation * _pos * glm::conjugate(parent->globalRotation);
        _pos += parent->globalPosition;
    }
    for (const auto &child : children)
    {
        child.second->flushTransform();
    }
}