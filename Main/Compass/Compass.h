#ifndef COMPASS
#define COMPASS

#include "../../Lib/Component/Behaviour/Behaviour.h"
#include "../../Lib/Component/Behaviour/BehaviourManager.h"

class Compass : public OpenEngine::Behaviour
{
    public:
    Compass(OpenEngine::Object & _obj);
    void init() override;
    void update(double delta) override;
    BaseComponent* instantiate() override{return new Compass(*this);}
};

#endif /*COMPASS*/