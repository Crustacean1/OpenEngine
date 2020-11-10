#ifndef COMPONENT
#define COMPONENT

namespace OpenEngine
{
    class Object;
    template<typename T>
    class ComponentFactory;

    class Component
    {
        friend ComponentFactory<Component>;
        ComponentFactory<Component> & factory;
        protected:
        Object & object;
        Component(Object & obj,ComponentFactory<Component> & _fact);
    public:
        ~Component();
    };
}; // namespace OpenEngine

#endif /*COMPONENT*/