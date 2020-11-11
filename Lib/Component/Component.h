#ifndef COMPONENT
#define COMPONENT

#include "ComponentFactory.h"

namespace OpenEngine
{
    class Object;
    class BaseComponentFactory;

    class BaseComponent
    {
        //friend ComponentFactory<T>;
        BaseComponentFactory &factory;

    protected:
        Object &object;
        BaseComponent(Object &_obj, BaseComponentFactory &_fact) : object(_obj), factory(_fact) {}

    public:
        ~BaseComponent()
        {
            factory.drop(this);
        }
    };
}; // namespace OpenEngine

#endif /*COMPONENT*/