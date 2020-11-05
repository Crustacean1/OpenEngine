#ifndef RENDERER
#define RENDERER

#include <memory>

namespace OpenEngine
{
    class Shader;
    class Render;
    
    class Renderer
    {
        std::shared_ptr<Render> myRender;
        protected:
        std::shared_ptr<Shader> myShader;

    public:
        Renderer(){}
        Renderer(std::shared_ptr<Render> _render,std::shared_ptr<Shader> _shader) :myShader(_shader){setRender(_render);}
        virtual void render() = 0;
        virtual void prepare() = 0;
        
        std::shared_ptr<Shader> getShader();
        void setShader(std::shared_ptr<Shader> _shader);

        void setRender(std::shared_ptr<Render> _render);
        ~Renderer();
    };
}; // namespace OpenEngine

#endif /*RENDERER*/