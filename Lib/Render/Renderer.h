#ifndef RENDERER
#define RENDERER

#include <memory>

namespace OpenEngine
{
    class Shader;
    class Render;
    class Object;
    
    class Renderer
    {
        std::shared_ptr<Render> myRender;
        protected:
        Object * myObject;
        bool shouldRender = true;
        std::shared_ptr<Shader> myShader;

    public:
        Renderer(Object * _obj) :myObject(_obj){}
        Renderer(Object * _obj, std::shared_ptr<Render> _render,std::shared_ptr<Shader> _shader) : myObject(_obj), myShader(_shader){setRender(_render);}
        virtual void render() = 0;
        virtual void prepare() = 0;
        
        std::shared_ptr<Shader> getShader();
        void setShader(std::shared_ptr<Shader> _shader);

        void setRender(std::shared_ptr<Render> _render);

        Object * getOwner(){return myObject;}
        ~Renderer();
    };
}; // namespace OpenEngine

#endif /*RENDERER*/