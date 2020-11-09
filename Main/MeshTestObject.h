#ifndef MESHTESTOBJECT
#define MESHTESTOBJECT

#include "../Lib/Object/Object.h"

namespace OpenEngine
{
    class MeshRenderer;
    class Render;
    class Shader;
    class Mesh;
} // namespace OpenEngine

class MeshTestObject : public OpenEngine::Object
{
    std::shared_ptr<OpenEngine::MeshRenderer> renderer;

public:
    MeshTestObject(Object _object) : Object::Object(_object) {}
    void init(const std::shared_ptr<OpenEngine::Render> &_render, std::shared_ptr<OpenEngine::Mesh> _mesh, const std::shared_ptr<OpenEngine::Shader> &shader);
};

#endif /*MESHTESTOBJECT*/