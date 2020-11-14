#include "FractalComponent.h"
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Render/Render.h"

using namespace OpenEngine;

void FractalComponent::init()
{
    if(counter<1){return;}

    auto newObject1 = new OpenEngine::Object();
    object.addChild(newObject1);
    newObject1->localPosition = glm::dquat(0,-1.5,0,0);
    newObject1->localRotation = glm::dquat(sqrt(2)/2,0,0,sqrt(2)/2);
    newObject1->localScale = glm::dquat(0,0.5,0.5,0.5);

    (new MeshRenderer(*newObject1,SimpleMesh<Vertex3pc,V3Index>::generateSphere(6,1),shader))->setManager(render);
    (new FractalComponent(*newObject1,bManager,render,shader,counter-1))->setManager(bManager);

    auto newObject2 = new OpenEngine::Object();
    object.addChild(newObject2);
    newObject2->localPosition = glm::dquat(0,1.5,0,0);
    newObject2->localRotation = glm::dquat(sqrt(2)/2,0,sqrt(2)/2,0);
    newObject2->localScale = glm::dquat(0,0.5,0.5,0.5);

    (new MeshRenderer(*newObject2,SimpleMesh<Vertex3pc,V3Index>::generateSphere(6,1),shader))->setManager(render);
    (new FractalComponent(*newObject2,bManager,render,shader,counter-1))->setManager(bManager);

}
void FractalComponent::update(double delta)
{

}