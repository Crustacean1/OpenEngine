#ifndef COMPONENT
#define COMPONENT

#include "ComponentManager.h"
#include "BaseComponent.h"
#include <string>

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
        Component(Object &_obj) : BaseComponent(_obj), manager(nullptr)
        {
            object.addComponent((T *)this);
        }

    public:
        std::string getTypeName() { return typeid(T).name(); }
        void setManager(ComponentManager<T> *_fact)
        {
            dropManager();
            manager = _fact;
            manager->add((T *)this);
        }
        void dropManager()
        {
            if (manager == nullptr)
            {
                return;
            }
            manager = nullptr;
            manager->drop((T *)this);
        }
        ~Component()
        {
            dropManager();
        }
    };
}; // namespace OpenEngine

#endif /*COMPONENT*/