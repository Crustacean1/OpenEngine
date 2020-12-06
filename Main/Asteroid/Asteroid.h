#ifndef ASTEROID
#define ASTEROID

#include "../../Lib/Component/Behaviour.h"

class Asteroid : public OpenEngine::Behaviour
{
    public:
    Asteroid(OpenEngine::Object * _obj) ;
    void init() override;
    void update(double delta) override;
};

#endif /*ASTEROID*/