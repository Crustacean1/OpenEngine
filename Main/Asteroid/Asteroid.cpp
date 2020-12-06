#include "Asteroid.h"
#include "../../Lib/Component/BehaviourManager.h"
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Render/MeshRenderer.h"
#include <stdlib.h>

using namespace OpenEngine;

Asteroid::Asteroid(Object * _obj,Material * _mat) : Behaviour(_obj)
{
    auto asteroid = SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(40,2);

    auto vertices = asteroid->getVertexBuffer().getData();
    float tabx[10];
    float taby[10];
    for(int i = 0;i<3;i++)
    {
        tabx[i] = (rand()%10);
        taby[i] = (rand()%10);
    }
    float sum;
    for(int i = 0;i<40;i++)
    {
        for(int j = 0;j<40;j++)
        {
            sum = 0;
            for(int k = 0;k<3;k++)
            {
                sum += sin(tabx[k]*i*(3.1415/20))+sin(taby[k]*j*(3.1415/20));
            }
            sum/=40;
            if(isnan(sum)||sum<-1||sum>1)
            {
                std::cout<<sum<<std::endl;
            }
            vertices[i*40+j].pos*=(1+sum);
        }
    }
    asteroid->computeTangentSpace();
    object->addComponent<MeshRenderer>()->setMesh(asteroid,_mat);
    object->localPosition = glm::dquat(0,0,5,0);
}
void Asteroid::init()
{

}
void Asteroid::update(double delta)
{

}
AsteroidField::AsteroidField(Object * _obj,Material * _mat) : Behaviour(_obj)
{
    for(int i = 0;i<400;i++)
    {
        auto ast = new Object(object);
        ast->addComponent<Asteroid>(_mat);
        ast->localPosition = glm::dquat(0,((rand()%20000)/100),((rand()%20000)/100),((rand()%20000)/100));
        auto s = (float)(rand()%30)/10.f;
        ast->localScale = glm::dquat(0,s,s,s);
    }
}