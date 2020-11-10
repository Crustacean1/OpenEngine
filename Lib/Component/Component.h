#ifndef COMPONENT
#define COMPONENT

#include "ComponentFactory.h"

namespace OpenEngine
{
    class Object;
    template <typename T>
    class ComponentFactory;

    template <typename T>
    class Component
    {
        //friend ComponentFactory<T>;
        ComponentFactory<T> &factory;

    protected:
        Object &object;
        Component(Object &_obj, ComponentFactory<T> &_fact) : object(_obj), factory(_fact) {}

    public:
        ~Component()
        {
            factory.drop((T*)this);
        }
    };
}; // namespace OpenEngine

#endif /*COMPONENT*/