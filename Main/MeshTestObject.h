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

    template<typename T>
    class ComponentFactory;
} // namespace OpenEngine
class RotationController : public OpenEngine::Behaviour
{
    glm::vec3 axis;
    public:
    RotationController(OpenEngine::Object & _obj,OpenEngine::ComponentFactory<Behaviour> &_fact,glm::vec3 _ax = glm::vec3(0,1,0)) : OpenEngine::Behaviour(_obj,_fact), axis(_ax){}
    double rotationSpeed = 1.5;
    void update(double delta);
};

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

#endif /*MESHTESTOBJECT*/