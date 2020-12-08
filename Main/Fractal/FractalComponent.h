#ifndef FRACTALCOMPONENT
#define FRACTALCOMPONENT

#include "../../Lib/Render/MeshRenderer.h"
#include "../../Lib/Component/Behaviour/Behaviour.h"
#include "../../Lib/Component/Behaviour/BehaviourManager.h"
#include "../../Lib/Shader/Shader.h"

class FractalComponent : public OpenEngine::Behaviour
{
    OpenEngine::BehaviourManager *bManager;
    OpenEngine::Render3D *render;
    OpenEngine::Shader * shader;

public:
    int counter;
    FractalComponent(OpenEngine::Object &_obj, OpenEngine::BehaviourManager *_bm, OpenEngine::Render3D *_r,OpenEngine::Shader * _s, unsigned int _count = 5) : 
                     OpenEngine::Behaviour(_obj), bManager(_bm), render(_r),shader(_s), counter(_count) {}
    void init() override;
    void update(double delta) override;
    BaseComponent* instantiate() override{return new FractalComponent(*this);}
};

#endif /*FRACTALCOMPONENT*/