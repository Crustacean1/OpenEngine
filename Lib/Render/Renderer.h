#ifndef RENDERER
#define RENDERER

#include "../Component/Component.h"
#include <tuple>

namespace OpenEngine
{
    class Shader;
    class Material;
    class Render3D;
    class Mesh;
    class Object;
    
    class Renderer : public Component<Renderer,Render3D>
    {
        friend Render3D;
        protected:
        bool shouldRender = true;

        std::list<Object*>::iterator it;

        Material * material = nullptr;
        Mesh * mesh= nullptr;
        int level = 5;

        void flush();

    public:
        template<typename T>
        Renderer(Object & _obj,T * _ptr) : Component(_obj,_ptr){}
        virtual void render() = 0;
        virtual void prepare() = 0;

        void setMaterial(Material * mat);
        Material * getMaterial();

        void setMesh(Mesh * _m,Material * mat);
        Mesh * getMesh();
        

        ~Renderer();
    };
}; // namespace OpenEngine

#endif /*RENDERER*/