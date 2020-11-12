#include "BehaviourManager.h"

void OpenEngine::BehaviourManager::update(double delta)
{
    for (auto &component : components)
    {
        component->update(delta);
    }
}
void OpenEngine::BehaviourManager::init()
{
    for (auto &component : components)
    {
        component->init();
    }
}