#ifndef COMPONENTFACTORY
#define COMPONENTFACTORY

#include <set>

namespace OpenEngine
{
    template<typename T>
    class ComponentManager;

    template<typename T>
    class ComponentFactory
    {
        friend T;
        friend ComponentManager<T>;
        std::set<T*> components;
        void drop(T* target); 
        public:
        template<typename... Args>
        T * create(Args... args);
    };

    template<typename T>
    template<typename... Args>
    T * ComponentFactory<T>::create(Args... args)
    {
        components.insert(new T(args...));
    }
    template<typename T>
    void ComponentFactory<T>::drop(T* target)
    {
        components.erase(target);
    }
};

#endif /*COMPONENTFACTORY*/