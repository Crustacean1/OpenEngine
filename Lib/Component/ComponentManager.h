#ifndef COMPONENTMANAGER
#define COMPONENTMANAGER

namespace OpenEngine
{
    template<typename T>
    class ComponentFactory;

    template<typename T>
    class ComponentManager
    {
        public:
        ComponentFactory<T> factory;
        virtual void update(double delta);
    };
};

#endif /*COMPONENTMANAGER*/