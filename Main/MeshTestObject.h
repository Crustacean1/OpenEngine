#ifndef MESHTESTOBJECT
#define MESHTESTOBJECT

#include "../Lib/Object/Object.h"
#include "../Lib/Component/Behaviour.h"
#include "../Lib/Component/BehaviourManager.h"
#include <iostream>

namespace OpenEngine
{
    class MeshRenderer;
    class Render3D;
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
    RotationController(OpenEngine::Object * _obj,glm::vec3 _ax = glm::vec3(0,1,0)) : OpenEngine::Behaviour(_obj), axis(_ax){}
    double rotationSpeed = 0.5;
    void update(double delta);
};
class GridController : public OpenEngine::Behaviour
{
    OpenEngine::Object * target;
    public:
    double gap = 10;
    GridController(OpenEngine::Object * _obj,OpenEngine::Object * _targ) : OpenEngine::Behaviour(_obj), target(_targ){} 
    void setTarget(OpenEngine::Object * _targ){target = _targ;}
    void update(double delta);
};
class Roughener : public OpenEngine::Behaviour
{
    public:
    Roughener(OpenEngine::Object * _obj):Behaviour(_obj){}
    void update(double delta){}
    void init();
};
#endif /*MESHTESTOBJECT*/