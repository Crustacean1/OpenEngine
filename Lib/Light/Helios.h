#ifndef HELIOS
#define HELIOS

#include "../Component/ComponentManager.h"
#include <map>

namespace OpenEngine
{
    class Light;
    class Camera;
    class Helios : public ComponentManager<Light,Helios>
    {
        public:
        void illuminate(Camera * cam);
    };
};

#endif /*HELIOS*/