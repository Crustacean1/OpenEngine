#include "Compass.h"
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Material/Material.h"
#include "../../Lib/Render/MeshRenderer.h"
#include "../../Lib/Render/Render.h"
#include "../../Lib/Component/Behaviour/BehaviourManager.h"
#include "../../Lib/Shader/Shader.h"
#include "../../Lib/Object/Object.h"

using namespace OpenEngine;

Compass::Compass(OpenEngine::Object & _obj) : OpenEngine::Behaviour(_obj,this)
{
    SimpleMesh<Vertex3pc,V2Index> * mesh = new SimpleMesh<Vertex3pc,V2Index>();

    mesh->getVertexBuffer().setBuffer(4);
    mesh->getIndexBuffer().setBuffer(3);
    auto *vertices = mesh->getVertexBuffer().getData();
    auto *indices = mesh->getIndexBuffer().getData();
    vertices[0].pos = glm::vec3(0,0,0);
    vertices[0].col = glm::vec3(0.5,0.5,0.5);
    vertices[1].pos = glm::vec3(1,0,0);
    vertices[1].col = glm::vec3(1,0,0);
    vertices[2].pos = glm::vec3(0,1,0);
    vertices[2].col = glm::vec3(0,1,0);
    vertices[3].pos = glm::vec3(0,0,1);
    vertices[3].col = glm::vec3(0,0,1);
    indices[0].set(0,1);
    indices[1].set(0,2);
    indices[2].set(0,3);
    mesh->shape = GL_LINES;
    mesh->flush();

    Shader * shader = new Shader("Shaders/Shader7/shader7.vert","Shaders/Shader7/shader7.frag");
    EmptyMaterial * mat = new EmptyMaterial();
    mat->shader = shader;
    object.addComponent<MeshRenderer>()->setMesh(mesh,mat);
}
void Compass::init(){}
void Compass::update(double delta){}