#ifndef BEHAVIOUR
#define BEHAVIOUR

#include "Component.h"

namespace OpenEngine
{
    class Behaviour : public BaseComponent//Useless as of now, left for sake of clarity
    {
        public:
        Behaviour(Object & _obj, ComponentFactory<Behaviour> & _fact) : BaseComponent(_obj,_fact){}
        virtual void update(double delta) = 0;
    };
};

#endif /*BEHAVIOUR*/