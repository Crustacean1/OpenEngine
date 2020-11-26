#ifndef FRACTALCOMPONENT
#define FRACTALCOMPONENT

#include "../../Lib/Component/Behaviour.h"
#include "../../Lib/Render/MeshRenderer.h"
#include "../../Lib/Component/BehaviourManager.h"
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
};

#endif /*FRACTALCOMPONENT*/