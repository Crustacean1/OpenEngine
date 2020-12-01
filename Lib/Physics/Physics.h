#ifndef PHYSICS
#define PHYSICS

#include "../Component/ComponentManager.h"
#include "../Component/ManagerTypes.h"

namespace OpenEngine
{
    class Physical;
    class PhysicManager : public ComponentManager<Physical>, public Temporal
    {
        public:
        void update(double delta) override;
    };
};

#endif /*PHYSICS*/