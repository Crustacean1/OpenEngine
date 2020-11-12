#include "MeshTestObject.h"
#include "../Lib/Mesh/Mesh.h"
#include "../Lib/Render/MeshRenderer.h"
#include "../Lib/Shader/Shader.h"
#include <iostream>

/*void MeshTestObject::init(const std::shared_ptr<OpenEngine::Render> &_render, std::shared_ptr<OpenEngine::Mesh> _mesh, const std::shared_ptr<OpenEngine::Shader> &shader)
{
    renderer = std::shared_ptr<OpenEngine::MeshRenderer>(new OpenEngine::MeshRenderer(this));
    renderer->setMesh(_mesh);
    renderer->setShader(shader);
    renderer->setRender(_render);
}*/
float mod(float a, float b)
{
    return ((int)(a / b)) * b;
}

void RotationController::update(double delta)
{
    //std::cout << "I have no case and i must shite: " << object.localRotation.w << " " << object.localRotation.x << " " << object.localRotation.y << " " << object.localRotation.z << " " << std::endl;
    object.localRotation = (glm::dquat)glm::angleAxis((float)(delta * rotationSpeed), axis) * object.localRotation;
    object.flushTransform();
}

void GridController::update(double delta)
{
    if (target == nullptr)
    {
        return;
    }
    object.localPosition.x = mod(target->getGlobalPosition().x, gap);
    object.localPosition.y = mod(target->getGlobalPosition().y, gap);
    object.localPosition.z = mod(target->getGlobalPosition().z, gap);
}