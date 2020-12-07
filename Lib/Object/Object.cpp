#include "Object.h"
#include "../Component/Component.h"
#include "../Scene/Scene.h"

OpenEngine::Object::Object(Scene *_s) : transform(*this)
{
    scene = _s;
    parent = nullptr;
    scene->add(this);
}
OpenEngine::Object::Object(Object *_par) : transform(*this)
{
    _par->addChild(this);
}
void OpenEngine::Object::addChild(OpenEngine::Object *_obj)
{
    children.insert(_obj);
    _obj->dropScene();
    _obj->parent = this;
}
void OpenEngine::Object::dropChild(OpenEngine::Object *_obj)
{
    _obj->parent = nullptr;
    _obj->scene = getScene();
    children.erase(_obj);
}

OpenEngine::Object::~Object()
{
    for (const auto &child : children)
    {
        delete child;
    }
    for (auto &componentCat : components)
    {
        for (auto &component : componentCat.second)
        {
            delete component;
        }
    }
}
OpenEngine::Scene *OpenEngine::Object::getScene()
{
    if (parent == nullptr)
    {
        return scene;
    }
    return parent->getScene();
}
void OpenEngine::Object::setScene(OpenEngine::Scene *_s)
{
    if (parent != nullptr)
    {
        parent->dropChild(this);
        parent = nullptr;
    }
    if (_s == nullptr)
    {
        return;
    }
    scene = _s;
}
void OpenEngine::Object::dropScene()
{
    if (scene == nullptr)
    {
        return;
    }
    scene->drop(this);
    scene = nullptr;
}