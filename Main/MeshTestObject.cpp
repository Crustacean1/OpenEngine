#include "MeshTestObject.h"
#include "../Lib/Mesh/Mesh.h"
#include "../Lib/Render/MeshRenderer.h"
#include "../Lib/Shader/Shader.h"

void MeshTestObject::init(const std::shared_ptr<OpenEngine::Render> & _render,const std::shared_ptr<OpenEngine::Shader> & shader)
{
    renderer = std::shared_ptr<OpenEngine::MeshRenderer>(new OpenEngine::MeshRenderer(this));
    renderer->setMesh(std::shared_ptr<OpenEngine::Mesh>(new OpenEngine::Mesh));
    renderer->getMesh()->generatePlane(3,0.5);
    renderer->setShader(shader);
    renderer->setRender(_render);
}