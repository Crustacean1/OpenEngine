#include "BehaviourManager.h"

void OpenEngine::BehaviourManager::update(double delta)
{
    for (auto &component : components)
    {
        component->update(delta);
    }
}
void OpenEngine::BehaviourManager::add(Behaviour * _comp)
{
    _comp->init();
    components.push_back(_comp);
}