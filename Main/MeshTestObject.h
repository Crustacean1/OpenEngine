#ifndef MESHTESTOBJECT
#define MESHTESTOBJECT

#include "../Lib/Object/Object.h"
#include "../Lib/Component/Behaviour.h"
#include "../Lib/Component/BehaviourManager.h"
#include <iostream>

namespace OpenEngine
{
    class MeshRenderer;
    class Render;
    class Shader;
    class Mesh;
    class Object;

    template<typename T>
    class ComponentFactory;
} // namespace OpenEngine
class RotationController : public OpenEngine::Behaviour
{
    glm::vec3 axis;
    public:
    RotationController(OpenEngine::Object & _obj,glm::vec3 _ax = glm::vec3(0,1,0)) : OpenEngine::Behaviour(_obj), axis(_ax){}
    double rotationSpeed = 1.5;
    void update(double delta);
};
class GridController : public OpenEngine::Behaviour
{
    OpenEngine::Object * target;
    public:
    double gap = 1;
    GridController(OpenEngine::Object & _obj,OpenEngine::Object * _targ) : OpenEngine::Behaviour(_obj), target(_targ){} 
    void setTarget(OpenEngine::Object * _targ){target = _targ;}
    void update(double delta);
};
/*
class MeshTestObject : public OpenEngine::Object
{
    std::shared_ptr<OpenEngine::MeshRenderer> renderer;
    std::shared_ptr<RotationController> controller;

public:
    MeshTestObject(OpenEngine::BehaviourManager & manager,glm::vec3 _ax = glm::vec3(0,1,0)) :
     Object::Object(),
     controller(manager.factory.create<RotationController>(*this,manager.factory,_ax)){}
    void init(const std::shared_ptr<OpenEngine::Render> &_render, std::shared_ptr<OpenEngine::Mesh> _mesh, const std::shared_ptr<OpenEngine::Shader> &shader);
};
*/
#endif /*MESHTESTOBJECT*/