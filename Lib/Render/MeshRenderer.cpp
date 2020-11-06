#include "MeshRenderer.h"
#include "../Mesh/Mesh.h"
#include <iostream>

OpenEngine::MeshRenderer::MeshRenderer() : mode(GL_TRIANGLES)
{
}

void display(OpenEngine::Vertex3p *v)
{
    std::cout << v[0].pos.x << " " << v[0].pos.y << " " << v[0].pos.z << std::endl;
    std::cout << v[1].pos.x << " " << v[1].pos.y << " " << v[1].pos.z << std::endl;
    std::cout << v[10].pos.x << " " << v[10].pos.y << " " << v[10].pos.z << std::endl;
}

void OpenEngine::MeshRenderer::render()
{
    myMesh->bind();
    glDrawElements(mode,myMesh->getMeshSize()*3,GL_UNSIGNED_INT,0);
}
void OpenEngine::MeshRenderer::prepare()
{
}