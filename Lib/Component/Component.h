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
        Object & object;
        ComponentFactory<Component> & factory;
        
        Component(Object & obj,ComponentFactory<Component> & _fact);
    public:
        ~Component();
    };
}; // namespace OpenEngine

#endif /*COMPONENT*/