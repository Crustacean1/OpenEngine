#ifndef COMPONENT
#define COMPONENT

#include "ComponentManager.h"
#include "BaseComponent.h"

namespace OpenEngine
{
    class Object;

    template <typename T>
    class ComponentManager;

    template <typename T>
    class Component : public BaseComponent
    {
        friend ComponentManager<T>;

        ComponentManager<T> *manager = nullptr;

    protected:
        Component(Object &_obj, ComponentManager<T> *_fact = nullptr) : BaseComponent(_obj), manager(_fact)
        {
            if (manager != nullptr)
            {
                manager->add((T *)this);
            }
        }

    public:
        void setManager(ComponentManager<T> *_fact)
        {
            dropManager();
            manager = _fact;
            manager->add((T*)this);
        }
        void dropManager()
        {
            if (manager == nullptr)
            {
                return;
            }
            manager = nullptr;
            manager->drop((T*)this);
        }
        ~Component()
        {
            manager->drop((T *)this);
        }
    };
}; // namespace OpenEngine

#endif /*COMPONENT*/