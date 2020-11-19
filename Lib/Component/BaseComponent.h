#ifndef BASECOMPONENT
#define BASECOMPONENT

#include "../Object/Object.h"

namespace OpenEngine
{
    class Object;
    class Scene;

    class BaseComponent
    {
        protected:

        BaseComponent(Object & _parent) : object(_parent){}
    public:
        Object &object;
        virtual void setManager(Scene * _s);
        virtual ~BaseComponent() {}
    };

}; // namespace OpenEngine

#endif /*BASECOMPONENT*/