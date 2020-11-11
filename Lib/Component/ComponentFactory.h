#ifndef COMPONENTFACTORY
#define COMPONENTFACTORY

#include <set>
//#include <iostream>

namespace OpenEngine
{
    template <typename T>
    class ComponentManager;
    
    class BaseComponent;
    class Object;

    class BaseComponentFactory
    {
        public:
        virtual void drop(BaseComponent * target) = 0;
    };

    template <typename T>
    class ComponentFactory : BaseComponentFactory
    {
        friend T;
        friend ComponentManager<T>;
        friend BaseComponent;
        std::set<T *> components;

    public:
        template <typename K, typename... Args>
        K *create(Object &_obj, ComponentFactory<T> &_fact, Args... args);
        void drop(BaseComponent *target);
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
    void ComponentFactory<T>::drop(BaseComponent *target)
    {
        components.erase((T*)target);
    }
}; // namespace OpenEngine

#endif /*COMPONENTFACTORY*/