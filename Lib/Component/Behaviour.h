#ifndef BEHAVIOUR
#define BEHAVIOUR

#include "Component.h"

namespace OpenEngine
{
    class Behaviour : public Component //Useless as of now, left for sake of clarity
    {
        public:
        Behaviour(Object & _obj, ComponentFactory<Component> & _fact) : Component(_obj,_fact){}
    };
};

#endif /*BEHAVIOUR*/