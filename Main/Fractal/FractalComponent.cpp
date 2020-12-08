#include "FractalComponent.h"
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Render/Render.h"
#include "../../Lib/Object/Object.h"

using namespace OpenEngine;

void FractalComponent::init()
{
    if(counter<1){return;}

    auto newObject1 = new OpenEngine::Object(object);
    newObject1->transform.localPosition = glm::dquat(0,-1.5,0,0);
    newObject1->transform.localRotation = glm::dquat(sqrt(2)/2,0,0,sqrt(2)/2);
    newObject1->transform.localScale = glm::dquat(0,0.5,0.5,0.5);

    //newObject1->addComponent<MeshRenderer>(SimpleMesh<Vertex3pc,V3Index>::generateSphere(6,1),nullptr,shader)->setManager(render);
    //newObject1->addComponent<FractalComponent>(bManager,render,shader,counter-1)->setManager(bManager);

    auto newObject2 = new OpenEngine::Object(object);
    newObject2->transform.localPosition = glm::dquat(0,1.5,0,0);
    newObject2->transform.localRotation = glm::dquat(sqrt(2)/2,0,sqrt(2)/2,0);
    newObject2->transform.localScale = glm::dquat(0,0.5,0.5,0.5);

    //newObject2->addComponent<MeshRenderer>(SimpleMesh<Vertex3pc,V3Index>::generateSphere(6,1),nullptr,shader)->setManager(render);
    //newObject2->addComponent<FractalComponent>(bManager,render,shader,counter-1)->setManager(bManager);

}
void FractalComponent::update(double delta)
{

}