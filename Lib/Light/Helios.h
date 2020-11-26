#ifndef HELIOS
#define HELIOS

#include "../Component/ComponentManager.h"
#include "../Component/ManagerTypes.h"
#include <map>

namespace OpenEngine
{
    class Light;
    class Camera;
    class Helios : public ComponentManager<Light>, public Passive
    {
        public:
        void illuminate(Camera * cam);
    };
};

#endif /*HELIOS*/