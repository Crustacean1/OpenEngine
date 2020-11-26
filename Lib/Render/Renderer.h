#ifndef RENDERER
#define RENDERER

#include "../Component/Component.h"
#include <tuple>

namespace OpenEngine
{
    class Shader;
    class Material3D;
    class Render3D;
    class Mesh;
    class Object;
    
    class Renderer : public Component<Renderer,Render3D>
    {
        friend Render3D;
        protected:
        bool shouldRender = true;
        std::list<std::tuple<Material3D*,Mesh*,std::list<Object*>::iterator>> meshes;
        void assignMeshes();
        void dropMeshes();

    public:
        Renderer(Object & _obj);
        virtual void render() = 0;
        virtual void prepare() = 0;

        int getIndexOf(Mesh * _m);

        void setMaterial(Material3D * mat,unsigned int i);
        Material3D * getMaterial(unsigned int i);

        void addMesh(Mesh * _m,Material3D * _mat = nullptr);
        void dropMesh(unsigned int _id);
        void setMesh(Mesh * _m,unsigned int id);
        Mesh * getMesh(unsigned int _id);
        unsigned int getMeshesCount();
        

        ~Renderer();
    };
}; // namespace OpenEngine

#endif /*RENDERER*/