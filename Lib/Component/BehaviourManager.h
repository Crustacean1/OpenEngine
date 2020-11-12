#ifndef BEHAVIOURMANAGER
#define BEHAVIOURMANAGER

#include "ComponentManager.h"
#include "Behaviour.h"

namespace OpenEngine
{
    class BehaviourManager : public ComponentManager<Behaviour>
    {
        public:
        void init();
        void update(double delta);
    };
};

#endif /*BEHAVIOURMANAGER*/