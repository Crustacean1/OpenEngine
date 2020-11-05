#include "MeshRenderer.h"
#include "../Mesh/Mesh.h"

OpenEngine::MeshRenderer::MeshRenderer() : mode(GL_TRIANGLES)
{

}

void OpenEngine::MeshRenderer::render()
{
    myMesh->bind();
    glDrawElements(mode,myMesh->getMeshSize(),GL_UNSIGNED_INT,0);
}
void OpenEngine::MeshRenderer::prepare()
{
    
}