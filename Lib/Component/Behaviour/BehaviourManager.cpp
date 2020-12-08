#include "BehaviourManager.h"

unsigned int OpenEngine::BehaviourManager::mainIndex = 0;
std::map<unsigned int,OpenEngine::BehaviourManager*> OpenEngine::BehaviourManager::managers;

void OpenEngine::BehaviourManager::update(double delta)
{
    for (auto &component : components)
    {
        component->update(delta);
    }
}