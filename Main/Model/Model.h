#ifndef MODEL
#define MODEL

#include "../../Lib/Component/Behaviour/Behaviour.h"
#include "../../Lib/Shader/Shader.h"
#include "../../Lib/Component/Behaviour/BehaviourManager.h"


class Model : public OpenEngine::Behaviour
{
    OpenEngine::Shader * shader;
    public:
    Model(OpenEngine::Object &_obj,OpenEngine::Shader * _s) : Behaviour(_obj),shader(_s){}
    void update(double delta ) override;
    void init() override;
    BaseComponent* instantiate() override{return new Model(*this);}
};

#endif /*MODEL*/