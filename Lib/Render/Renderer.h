#ifndef RENDERER
#define RENDERER

#include "../Component/Component.h"
#include <memory>

namespace OpenEngine
{
    class Shader;
    class Render;
    class Object;
    class Material;
    
    class Renderer : public Component<Renderer>
    {
        protected:
        bool shouldRender = true;
        

    public:
        Shader * myShader = nullptr;
        Renderer(Object & _obj,Shader * _shader =nullptr) : myShader(_shader),Component(_obj){}
        virtual void render() = 0;
        virtual void prepare() = 0;
        
        Shader * getShader();
        void setShader(Shader * _shader);

        ~Renderer(){}
    };
}; // namespace OpenEngine

#endif /*RENDERER*/