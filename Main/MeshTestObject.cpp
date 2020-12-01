#include "MeshTestObject.h"
#include "../Lib/Mesh/Mesh.h"
#include "../Lib/Render/MeshRenderer.h"
#include "../Lib/Shader/Shader.h"
#include "../Lib/Material/Material.h"
#include <iostream>
#include <ctime>
#include <stdlib.h>

float mod(float a, float b)
{
    return ((int)(a / b)) * b;
}

void RotationController::update(double delta)
{
    //std::cout << "I have no case and i must shite: " << object.localRotation.w << " " << object.localRotation.x << " " << object.localRotation.y << " " << object.localRotation.z << " " << std::endl;
    object->localRotation = (glm::dquat)glm::angleAxis((float)(delta * rotationSpeed), axis) * object->localRotation;
    object->flushTransform();
}

void GridController::update(double delta)
{
    if (target == nullptr)
    {
        return;
    }
    object->localPosition.x = mod(target->getGlobalPosition().x, gap);
    object->localPosition.y = mod(target->getGlobalPosition().y, gap);
    object->localPosition.z = mod(target->getGlobalPosition().z, gap);
}
void Roughener::init()
{
    srand(time(0));
    auto * comp = object->getComponent<OpenEngine::MeshRenderer>(0);
    if(comp==nullptr){return;}
    auto material  = (OpenEngine::Material3D*)comp->getMaterial();
    material->norm.create(64,64,3);
    unsigned char * data = material->norm.getData();

    float xangle,yangle;

    for(unsigned int i = 0,k = 0;i<64;i++)
    {
        for(unsigned int j = 0;j<64;j++)
        {
            xangle = 80 + (float)(rand()%9999)/500.f;
            yangle = 80 + (float)(rand()%9999)/500.f;
            data[k++] = std::min(255.f,(128.f*cos(glm::radians(xangle))*cos(glm::radians(yangle))+ 128.f));
            data[k++] = std::min(255.f,(128.f*sin(glm::radians(xangle))*cos(glm::radians(yangle)) + 128.f));
            data[k++] = std::min(255.f,(128.f*sin(glm::radians(yangle)) + 128.f));
            
        }
    }
    material->norm.flush();
    comp->getMaterial()->activate();
}