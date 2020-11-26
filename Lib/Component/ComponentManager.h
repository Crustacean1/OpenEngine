#ifndef COMPONENTMANAGER
#define COMPONENTMANAGER

#include <list>
#include "BaseComponent.h"
//Note: put BaseComponent in separate file top avoid circular dependencies
namespace OpenEngine
{
    template <typename T,typename M>
    class Component;

    template <typename T>
    class ComponentManager
    {
    protected:
        //template<typename M>
        //friend Component<T,M>;

    protected:
        std::list<T *> components;

    public:
        virtual void add(T *_ptr);
        virtual void drop(T *_ptr);
        static std::string getTypename() { return typeid(T).name(); }
    };
    template <typename T>
    void ComponentManager<T>::add(T *_ptr)
    {
        components.push_back(_ptr);
    }
    template <typename T>
    void ComponentManager<T>::drop(T *_ptr)
    {
        for (auto it = components.begin(); it != components.end(); it++)
        {
            if ((*it) == _ptr)
            {
                components.erase(it);
                break;
            }
        }
    }
}; // namespace OpenEngine

#endif /*COMPONENTMANAGER*/