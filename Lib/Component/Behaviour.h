#ifndef BEHAVIOUR
#define BEHAVIOUR

#include "Component.h"

namespace OpenEngine
{
    class Behaviour : public Component<Behaviour> //Useless as of now, left for sake of clarity
    {
        public:
        Behaviour(Object & _obj, ComponentFactory<Behaviour> & _fact) : Component(_obj,_fact){}
        virtual void update(double delta) = 0;
    };
};

#endif /*BEHAVIOUR*/