#ifndef COMPONENTMANAGER
#define COMPONENTMANAGER

#include <set>
#include <map>
//Note: put BaseComponent in separate file top avoid circular dependencies
namespace OpenEngine
{

    template <typename T, typename M>
    class ComponentManager
    {
        static std::map<unsigned int, M*> &__managers;
        static unsigned int &__mainIndex;

    protected:
        std::set<T *> components;

    public:
        virtual T *drop(T *_ptr);
        virtual void add(T *_ptr);

        static M *getInstance(T *ptr, unsigned int id);

        ComponentManager(M *_ptr);

        virtual ~ComponentManager(){};
    };
    template <typename T, typename M>
    T *ComponentManager<T, M>::drop(T *_ptr)
    {
        auto it = components.find(_ptr);
        if (it != components.end())
        {
            return *it;
        }
        return nullptr;
    }
    template <typename T, typename M>
    void ComponentManager<T, M>::add(T *_ptr)
    {
        components.insert(_ptr);
    }
    template <typename T, typename M>
    M *ComponentManager<T, M>::getInstance(T *_ptr, unsigned int id)
    {
        if (id < __mainIndex)
        {
            __managers[id]->add(_ptr);
            return __managers[id];
        }
        return nullptr;
    }
    template <typename T, typename M>
    ComponentManager<T, M>::ComponentManager(M *_ptr) { __managers[__mainIndex++] = _ptr; }
}; // namespace OpenEngine

template <typename T, typename M>
std::map<unsigned int, M *> &OpenEngine::ComponentManager<T, M>::__managers = M::managers;

template <typename T, typename M>
unsigned int &OpenEngine::ComponentManager<T, M>::__mainIndex = M::mainIndex;

#endif /*COMPONENTMANAGER*/