#include "Physics.h"
#include "Physical.h"

//unsigned int OpenEngine::PhysicManager::mainIndex;
std::map<unsigned int,OpenEngine::PhysicManager*> OpenEngine::PhysicManager::managers;

void OpenEngine::PhysicManager::update(double delta)
{
    for(auto & component: components)
    {
        component->update(delta);
    }
}