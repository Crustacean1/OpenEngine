#ifndef BEHAVIOURMANAGER
#define BEHAVIOURMANAGER

#include "ComponentManager.h"
#include "Behaviour.h"
#include "ManagerTypes.h"

namespace OpenEngine
{
    class BehaviourManager : public ComponentManager<Behaviour>, public Temporal
    {
        public:
        void add(Behaviour * _comp) override;
        void update(double delta);
    };
};

#endif /*BEHAVIOURMANAGER*/