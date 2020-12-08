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
        friend Object;
        M *manager;
        Component(Object &_obj, T *ptr, unsigned int id = 0);
        void setManagerInstance(T * ptr,unsigned int id = 0);
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
    void Component<T, M>::setManagerInstance(T * ptr,unsigned int id)
    {
        if (manager != nullptr)
        {
            manager = M::getInstance(manager->drop((T*)this), id);
            return;
        }
        manager = M::getInstance(ptr,id);
    }
}; // namespace OpenEngine

#endif /*COMPONENT*/