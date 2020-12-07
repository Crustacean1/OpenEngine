#ifndef COMPONENT
#define COMPONENT

#include "BaseComponent.h"
#include <iostream>

namespace OpenEngine
{
    class Object;

    template <typename T,typename M>
    class ComponentManager;

    template <typename T, typename M>
    class Component : public BaseComponent
    {
        friend M;

    protected:
        M *manager;
        Component(Object &_obj, T *ptr, unsigned int id = 0);
        void setManagerInstance(unsigned int id = 0);
        ~Component();

    public:
    };

    template <typename T, typename M>
    Component<T, M>::Component(Object &_obj, T *ptr, unsigned int id) : BaseComponent(_obj)
    {
        manager = M::getInstance(ptr, id);
    }

    template <typename T, typename M>
    Component<T, M>::~Component()
    {
        manager->drop((T*)this);
    }

    template <typename T, typename M>
    void Component<T, M>::setManagerInstance(unsigned int id)
    {
        if (manager != nullptr)
        {
            manager = M::getInstance(manager->drop(this), id);
        }
    }
}; // namespace OpenEngine

#endif /*COMPONENT*/