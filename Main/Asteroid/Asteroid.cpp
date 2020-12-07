#include "Asteroid.h"
#include "../../Lib/Component/Behaviour/BehaviourManager.h"
#include "../../Lib/Mesh/Mesh.h"
#include "../../Lib/Render/MeshRenderer.h"
#include "../../Lib/Object/Object.h"
#include <stdlib.h>

using namespace OpenEngine;

Asteroid::Asteroid(Object & _obj,Material * _mat) : Behaviour(_obj,this)
{
    auto asteroid = SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(40,2);

    auto vertices = asteroid->getVertexBuffer().getData();
    float tabx[10];
    float taby[10];
    for(int i = 0;i<3;i++)
    {
        tabx[i] = (rand()%4);
        taby[i] = (rand()%4);
    }
    float sum;
    for(int i = 0;i<40;i++)
    {
        for(int j = 0;j<40;j++)
        {
            sum = 0;
            for(int k = 0;k<3;k++)
            {
                sum += (4-tabx[k])*sin(tabx[k]*j*(3.14159265/19.5));
            }
            sum/=20;
            if(isnan(sum)||sum<-1||sum>1)
            {
                std::cout<<sum<<std::endl;
            }
            vertices[i*40+j].pos*=(1+sum);
        }
    }
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
AsteroidField::AsteroidField(Object & _obj,Material * _mat) : Behaviour(_obj,this)
{
    for(int i = 0;i<400;i++)
    {
        auto ast = new Object(object);
        ast->addComponent<Asteroid>(_mat);
        ast->transform.localPosition = glm::dquat(0,((rand()%40000)/100)-200,((rand()%40000)/100)-200,((rand()%40000)/100)-200);
        auto s = (float)(rand()%30)/10.f;
        ast->transform.localScale = glm::dquat(0,s,s,s);
    }
}