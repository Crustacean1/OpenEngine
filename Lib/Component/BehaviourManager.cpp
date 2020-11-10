#include "BehaviourManager.h"
#include "Behaviour.h"

void OpenEngine::BehaviourManager::update(double delta)
{
    auto components = getComponents();
    for (const auto &component : components)
    {
        component->update(delta);
    }
}