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
};
class AsteroidField : public OpenEngine::Behaviour
{

public:
    AsteroidField(OpenEngine::Object &_obj, OpenEngine::Material *mat);
    void init() override{}
    void update(double delta) override{}
};

#endif /*ASTEROID*/