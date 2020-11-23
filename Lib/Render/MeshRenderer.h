#ifndef MESHRENDERER
#define MESHRENDERER

#include "Renderer.h"

namespace OpenEngine
{
    class Mesh;
    class Shader;
    class Object;
    class Material;
    
    class MeshRenderer : public Renderer
    {
    protected:
        Mesh * myMesh;
        Material * material;

    public:
        MeshRenderer(Object & object,Mesh * _mesh = nullptr, Material * _mat = nullptr, Shader * _shader = nullptr);

        void render() override;
        void prepare() override;

        Mesh* getMesh() { return myMesh; }
        void setMesh(Mesh * _mesh) { myMesh = _mesh;}

        Material * getMaterial(){return material;}
        void setMaterial(Material * _mat){material = _mat;}
    };
}; // namespace OpenEngine

#endif /*MESHRENDERER*/