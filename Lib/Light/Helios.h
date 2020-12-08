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
        protected:
        friend ComponentManager<Light,Helios>;
        static std::map<unsigned int,Helios*> managers;
        static unsigned int mainIndex;

        public:
        Helios(): ComponentManager(this){}
        void illuminate(Camera * cam);
    };
};

#endif /*HELIOS*/