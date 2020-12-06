#ifndef COMPASS
#define COMPASS

#include "../../Lib/Component/Behaviour.h"
#include "../../Lib/Component/BehaviourManager.h"

class Compass : public OpenEngine::Behaviour
{
    public:
    Compass(OpenEngine::Object * _obj);
    void init() override;
    void update(double delta) override;
};

#endif /*COMPASS*/