#include "MeshRenderer.h"
#include "../Mesh/Mesh.h"
#include "../Object/Object.h"
#include "../Material/Material.h"

OpenEngine::MeshRenderer::MeshRenderer(Object & object, std::shared_ptr<Mesh> _mesh,Material * _mat, Shader * _shader) : material(_mat), myMesh(_mesh), Renderer::Renderer(object, _shader){}


void OpenEngine::MeshRenderer::render()
{
    myMesh->bind();
    material->update();
    glDrawElements(myMesh->getShape(), myMesh->getMeshSize() , GL_UNSIGNED_INT, 0);
}
void OpenEngine::MeshRenderer::prepare()
{
}