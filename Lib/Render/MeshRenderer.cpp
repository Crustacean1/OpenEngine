#include "MeshRenderer.h"
#include "../Mesh/Mesh.h"
#include "../Object/Object.h"

OpenEngine::MeshRenderer::MeshRenderer(Object & object, std::shared_ptr<Mesh> _mesh, Shader * _shader) : myMesh(_mesh), Renderer::Renderer(object, _shader){}


void OpenEngine::MeshRenderer::render()
{
    myMesh->bind();
    glDrawElements(myMesh->getShape(), myMesh->getMeshSize() , GL_UNSIGNED_INT, 0);
}
void OpenEngine::MeshRenderer::prepare()
{
}