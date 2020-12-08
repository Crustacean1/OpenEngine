#ifndef ASTEROID
#define ASTEROID
#include "../../Lib/Component/Behaviour/Behaviour.h"
#include "../../Lib/Component/Behaviour/BehaviourManager.h"

namespace OpenEngine
{
    class Material;
};

class Asteroid : public OpenEngine::Behaviour
{
public:
    Asteroid(OpenEngine::Object &_obj, OpenEngine::Material *mat);
    void init() override;
    void update(double delta) override;
    BaseComponent* instantiate() override{return new Asteroid(*this);}
};
class AsteroidField : public OpenEngine::Behaviour
{

public:
    AsteroidField(OpenEngine::Object &_obj, OpenEngine::Material *mat);
    void init() override{}
    void update(double delta) override{}
    BaseComponent* instantiate() override{return new AsteroidField(*this);}
};

#endif /*ASTEROID*/