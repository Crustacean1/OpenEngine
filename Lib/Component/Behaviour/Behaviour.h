#ifndef BEHAVIOUR
#define BEHAVIOUR

#include "../Component.h"

namespace OpenEngine
{
    class BehaviourManager;

    class Behaviour : public Component<Behaviour,BehaviourManager>//Useless as of now, left for sake of clarity
    {
        public:
        template<typename T>
        Behaviour(Object & _obj,T * _ptr) : Component(_obj,_ptr){}
        virtual void update(double delta){};
        virtual void init(){}
    };
};

#endif /*BEHAVIOUR*/