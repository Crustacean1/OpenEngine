#ifndef RENDERER
#define RENDERER

#include "../Component/Component.h"
#include <tuple>

namespace OpenEngine
{
    class Shader;
    class Material;
    class Render;
    class Mesh;
    class Object;
    
    class Renderer : public Component<Renderer>
    {
        friend Render;
        protected:
        bool shouldRender = true;
        std::list<std::tuple<Material*,Mesh*,std::list<Object*>::iterator>> meshes;
        void assignMeshes();
        void dropMeshes();

    public:
        Renderer(Object & _obj) : Component(_obj){}
        virtual void render() = 0;
        virtual void prepare() = 0;

        int getIndexOf(Mesh * _m);

        void setMaterial(Material * mat,unsigned int i);
        Material * getMaterial(unsigned int i);

        void addMesh(Mesh * _m,Material * _mat = nullptr);
        void dropMesh(unsigned int _id);
        void setMesh(Mesh * _m,unsigned int id);
        Mesh * getMesh(unsigned int _id);
        unsigned int getMeshesCount();
        

        ~Renderer(){dropMeshes();}
    };
}; // namespace OpenEngine

#endif /*RENDERER*/