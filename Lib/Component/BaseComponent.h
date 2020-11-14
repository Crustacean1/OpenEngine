#ifndef BASECOMPONENT
#define BASECOMPONENT

#include "../Object/Object.h"

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