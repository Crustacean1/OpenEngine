#ifndef COMPONENTFACTORY
#define COMPONENTFACTORY

#include <set>

namespace OpenEngine
{
    template<typename T>
    class ComponentFactory
    {
        std::set<T*> components;
        void drop(T* target); 
        public:
        template<typename... Args>
        T * create(Args... args);
    };
};

#endif /*COMPONENTFACTORY*/