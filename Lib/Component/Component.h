#ifndef COMPONENT
#define COMPONENT

#include "BaseComponent.h"
#include <iostream>

namespace OpenEngine
{
    class Object;

    template <typename T, typename M>
    class ComponentManager;

    template <typename T, typename M>
    class Component : public BaseComponent // T must inherit Component<T,M>
    {
        friend M;

    protected:
        friend Object;
        M *manager;
        Component(Object &_obj, unsigned int id = 0);
        ~Component();

    public:
        void setManagerInstance(unsigned int id = 0);
    };
    template <typename T, typename M>
    Component<T, M>::Component(Object &_obj, unsigned int id) : BaseComponent(_obj)
    {
        manager = M::getInstance((T *)this, id);
    }

    template <typename T, typename M>
    Component<T, M>::~Component()
    {
        manager->drop((T *)this);
    }

    template <typename T, typename M>
    void Component<T, M>::setManagerInstance(unsigned int id)
    {
        if (manager != nullptr)
        {
            auto tMan = M::getInstance((T *)this, id);
            if (tMan != nullptr)
            {
                manager = tMan;
            }
            return;
        }
    }
}; // namespace OpenEngine

#endif /*COMPONENT*/