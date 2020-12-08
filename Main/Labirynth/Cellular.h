#ifndef CELLULAR
#define CELLULAR

#include "../../Lib/Component/Behaviour/Behaviour.h"
#include "../../Lib/Component/Behaviour/BehaviourManager.h"

namespace OpenEngine{class Material3D;};

class Labirynth : public OpenEngine::Behaviour
{
    char *grid1;
    char *grid2;

    OpenEngine::Material3D * mat;

    unsigned int width;
    unsigned int depth;
    float scale;
    float probability = 0.75;
    int threshold;
    unsigned int iterations;

    void iterate(int degree);
    void fill();
    void instantiate(int degree);
    void debug(char * ptr);

public:
    Labirynth(OpenEngine::Object &_obj,OpenEngine::Material3D * _m, unsigned int _w, unsigned int _d,int _t,unsigned int _i, float _s = 1,float _p = 0.75f) :
     Behaviour(_obj), scale(_s), width(_w), depth(_d),probability(_p),threshold(_t),mat(_m),iterations(_i) {}
    void init() override;
    void update(double delta) override {}
    BaseComponent* instantiate() override{return new Labirynth(*this);}
};

#endif /*CELLULAR*/