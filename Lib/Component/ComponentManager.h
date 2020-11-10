#ifndef COMPONENTMANAGER
#define COMPONENTMANAGER

#include "ComponentFactory.h"

namespace OpenEngine
{
    template<typename T>
    class ComponentFactory;

    template<typename T>
    class ComponentManager
    {
        protected:
        std::set<T*> & getComponents(){return factory.components;}
        public:
        ComponentFactory<T> factory;
    };
};

#endif /*COMPONENTMANAGER*/