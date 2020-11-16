#ifndef UNIFORM
#define UNIFORM

namespace OpenEngine
{
    class Shader;
    class Uniform
    {
        public:
        Shader * shader;

        Uniform(){}
        Uniform(Shader * _sh) : shader(_sh){}
        
        virtual void update() = 0;
    };
};

#endif /*UNIFORM*/