#ifndef BEHAVIOURMANAGER
#define BEHAVIOURMANAGER

#include "ComponentManager.h"

namespace OpenEngine
{
    class Behaviour;
    class BehaviourManager : public ComponentManager<Behaviour>
    {
        public:
        void update(double delta);
    };
};

#endif /*BEHAVIOURMANAGER*/