#ifndef PHYSICS
#define PHYSICS

#include "../Component/ComponentManager.h"
#include <map>

namespace OpenEngine
{
    class Physical;
    class PhysicManager : public ComponentManager<Physical, PhysicManager>
    {
    protected:
        template <typename K>
        PhysicManager(K *_ptr) : ComponentManager(_ptr) {}

        friend ComponentManager<Physical,PhysicManager>;
        static unsigned int mainIndex;
        static std::map<unsigned int,PhysicManager*> managers;

    public:
        PhysicManager() : ComponentManager(this) {}
        void update(double delta);
    };
}; // namespace OpenEngine

#endif /*PHYSICS*/