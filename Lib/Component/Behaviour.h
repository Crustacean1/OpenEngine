#ifndef BEHAVIOUR
#define BEHAVIOUR

#include "Component.h"

namespace OpenEngine
{
    class Behaviour : public Component<Behaviour>//Useless as of now, left for sake of clarity
    {
        public:
        Behaviour(Object & _obj, ComponentManager<Behaviour> * _fact = nullptr) : Component(_obj,_fact){}
        virtual void update(double delta){};
        virtual void init(){}
    };
};

#endif /*BEHAVIOUR*/