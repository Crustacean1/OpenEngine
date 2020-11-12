#ifndef BASECOMPONENT
#define BASECOMPONENT

namespace OpenEngine
{
    class Object;

    class BaseComponent
    {
        protected:
        BaseComponent(Object & _parent) : object(_parent){}
    public:
        Object &object;
        virtual ~BaseComponent() {}
    };

}; // namespace OpenEngine

#endif /*BASECOMPONENT*/