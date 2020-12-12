#include "MeshTestObject.h"
#include "../Lib/Mesh/Mesh.h"
#include "../Lib/Render/MeshRenderer.h"
#include "../Lib/Render/Render.h"
#include "../Lib/Shader/Shader.h"
#include "../Lib/Material/Material.h"
#include "../Lib/Loaders/TextureLoader/TextureLoader.h"
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
    object.transform.localRotation = (glm::dquat)glm::angleAxis((float)(delta * rotationSpeed), axis) * object.transform.localRotation;
    object.transform.flushTransform();
}

void GridController::update(double delta)
{
    if (target == nullptr)
    {
        return;
    }
    object.transform.localPosition.x = mod(target->transform.getGlobalPosition().x, gap);
    object.transform.localPosition.y = mod(target->transform.getGlobalPosition().y, gap);
    object.transform.localPosition.z = mod(target->transform.getGlobalPosition().z, gap);
}
void Roughener::init()
{
    srand(time(0));
    auto * comp = object.getComponent<OpenEngine::MeshRenderer>(0);
    if(comp==nullptr){return;}
    auto material  = (OpenEngine::Material3D*)comp->getMaterial();
    material->norm->createFromColor(64,64,3);
    unsigned char * data = material->norm->getData();

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
    material->norm->flush();
    comp->getMaterial()->activate();
}