#include "Asteroid.h"
#include "../../Lib/Component/Behaviour/BehaviourManager.h"
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Render/MeshRenderer.h"
#include "../../Lib/Render/Render.h"
#include "../../Lib/Object/Object.h"
#include <stdlib.h>

using namespace OpenEngine;

Asteroid::Asteroid(Object & _obj,Mesh * _mesh, Material * _mat) : Behaviour(_obj)
{
    auto asteroid = SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(40,2);

    auto vertices = asteroid->getVertexBuffer().getData();
    
    asteroid->computeTangentSpace();
    object.addComponent<MeshRenderer>()->setMesh(asteroid,_mat);
    object.transform.localPosition = glm::dquat(0,0,5,0);
}
void Asteroid::init()
{

}
void Asteroid::update(double delta)
{

}
AsteroidField::AsteroidField(Object & _obj,Material * _mat) : Behaviour(_obj)
{
    auto * aMesh = SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(30,1);
    for(int i = 0;i<400;i++)
    {
        auto ast = new Object(object);
        ast->addComponent<Asteroid>(aMesh,_mat);
        ast->transform.localPosition = glm::dquat(0,((rand()%40000)/100)-200,((rand()%40000)/100)-200,((rand()%40000)/100)-200);
        auto s = (float)(rand()%30)/10.f;
        ast->transform.localScale = glm::dquat(0,s,s,s);
    }
}