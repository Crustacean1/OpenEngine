#include "Physics.h"
#include "Physical.h"

void OpenEngine::PhysicManager::update(double delta)
{
    for(auto & component: components)
    {
        component->update(delta);
    }
}