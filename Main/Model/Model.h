#ifndef MODEL
#define MODEL

#include "../../Lib/Component/Behaviour.h"
#include "../../Lib/Shader/Shader.h"


class Model : public OpenEngine::Behaviour
{
    OpenEngine::Shader * shader;
    public:
    Model(OpenEngine::Object &_obj,OpenEngine::Shader * _s) : Behaviour(_obj),shader(_s){}
    void update(double delta ) override;
    void init() override;
};

#endif /*MODEL*/