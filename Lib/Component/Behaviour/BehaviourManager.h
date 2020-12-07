#ifndef BEHAVIOURMANAGER
#define BEHAVIOURMANAGER

#include "../ComponentManager.h"
#include "Behaviour.h"
namespace OpenEngine
{
    class BehaviourManager : public ComponentManager<Behaviour,BehaviourManager>
    {
        public:
        void add(Behaviour * _comp) override;
        void update(double delta);
    };
};

#endif /*BEHAVIOURMANAGER*/