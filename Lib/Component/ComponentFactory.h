#ifndef COMPONENTFACTORY
#define COMPONENTFACTORY

#include <set>
//#include <iostream>

namespace OpenEngine
{
    template <typename T>
    class ComponentManager;
    template <typename T>
    class Component;
    class Object;

    template <typename T>
    class ComponentFactory
    {
        friend T;
        friend ComponentManager<T>;
        friend Component<T>;
        std::set<T *> components;
        void drop(T *target);

    public:
        template <typename K, typename... Args>
        K *create(Object &_obj, ComponentFactory<T> &_fact, Args... args);
        ~ComponentFactory()
        {
            //std::cout<<"quitting"<<std::endl;
        }
    };

    template <typename T>
    template <typename K, typename... Args>
    K *ComponentFactory<T>::create(Object &_obj, ComponentFactory<T> &_fact, Args... args)
    {
        components.insert(new K(_obj, _fact, args...));
    }
    template <typename T>
    void ComponentFactory<T>::drop(T *target)
    {
        components.erase(target);
    }
}; // namespace OpenEngine

#endif /*COMPONENTFACTORY*/