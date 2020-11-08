#include "MeshTestObject.h"
#include "../Lib/Mesh/Mesh.h"
#include "../Lib/Render/MeshRenderer.h"
#include "../Lib/Shader/Shader.h"

void MeshTestObject::init(const std::shared_ptr<OpenEngine::Render> &_render, std::shared_ptr<OpenEngine::Mesh> _mesh, const std::shared_ptr<OpenEngine::Shader> &shader)
{
    renderer = std::shared_ptr<OpenEngine::MeshRenderer>(new OpenEngine::MeshRenderer(this));
    renderer->setMesh(_mesh);
    renderer->setShader(shader);
    renderer->setRender(_render);
}