#ifndef BEHAVIOURMANAGER
#define BEHAVIOURMANAGER

#include "../ComponentManager.h"
#include "Behaviour.h"
#include <map>

namespace OpenEngine
{
    class BehaviourManager : public ComponentManager<Behaviour, BehaviourManager>
    {
    protected:
        friend ComponentManager<Behaviour, BehaviourManager>;
        static std::map<unsigned int,BehaviourManager *> managers;
        //static unsigned int mainIndex;

    public:
        BehaviourManager(Scene * _scene) : ComponentManager(_scene) {}
        void update(double delta);
    };
}; // namespace OpenEngine

#endif /*BEHAVIOURMANAGER*/