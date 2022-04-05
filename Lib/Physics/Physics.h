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

        friend ComponentManager<Physical,PhysicManager>;
        //static unsigned int mainIndex;
        static std::map<unsigned int,PhysicManager*> managers;

    public:
        PhysicManager(Scene * _scene) : ComponentManager(_scene) {}
        void update(double delta);
    };
}; // namespace OpenEngine

#endif /*PHYSICS*/