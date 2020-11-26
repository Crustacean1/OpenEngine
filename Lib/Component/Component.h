#ifndef COMPONENT
#define COMPONENT

#include "ComponentManager.h"
#include "BaseComponent.h"
#include "../Scene/Scene.h"
#include <string>
#include <iostream>

namespace OpenEngine
{
    class Object;

    template <typename T>
    class ComponentManager;

    template <typename T, typename M>
    class Component : public BaseComponent
    {
        friend M;
        friend Object;

        void setManager(Scene *_s)
        {
            dropManager();
            manager = _s->getComponentManager<M>();
            if(manager==nullptr){return;}
            manager->add((T *)this);
        }
        void dropManager()
        {
            if (manager == nullptr)
            {
                return;
            }
            manager = manager = nullptr;
            manager->drop((T *)this);
        }

    protected:

        M *manager = nullptr;
        Component(Object &_obj) : BaseComponent(_obj), manager(nullptr)
        {}

    public:
        std::string getTypeName() { return typeid(T).name(); }

        ~Component()
        {
            dropManager();
        }
    };
}; // namespace OpenEngine

#endif /*COMPONENT*/