#include "MeshRenderer.h"
#include "../Mesh/Mesh.h"
#include "../Object/Object.h"
#include <iostream>

OpenEngine::MeshRenderer::MeshRenderer(Object * object, std::shared_ptr<Mesh> _mesh, std::shared_ptr<Render> _render, std::shared_ptr<Shader> _shader) : myMesh(_mesh), Renderer::Renderer(object,_render, _shader),mode(GL_TRIANGLES) {}

void display(OpenEngine::Vertex3p *v)
{
    std::cout << v[0].pos.x << " " << v[0].pos.y << " " << v[0].pos.z << std::endl;
    std::cout << v[1].pos.x << " " << v[1].pos.y << " " << v[1].pos.z << std::endl;
    std::cout << v[10].pos.x << " " << v[10].pos.y << " " << v[10].pos.z << std::endl;
}

void OpenEngine::MeshRenderer::render()
{
    myMesh->bind();
    glDrawElements(mode, myMesh->getMeshSize() , GL_UNSIGNED_INT, 0);
}
void OpenEngine::MeshRenderer::prepare()
{
}