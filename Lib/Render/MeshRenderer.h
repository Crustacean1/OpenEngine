#ifndef MESHRENDERER
#define MESHRENDERER

#include "Renderer.h"

namespace OpenEngine
{
    class Mesh;
    class Shader;
    class Object;
    class MeshRenderer : public Renderer
    {
    protected:
        std::shared_ptr<Mesh> myMesh;
        Material * material;

    public:
        MeshRenderer(Object & object, std::shared_ptr<Mesh> _mesh = nullptr, Material * _mat = nullptr, Shader * _shader = nullptr);

        void render() override;
        void prepare() override;

        std::shared_ptr<Mesh> getMesh() { return myMesh; }
        void setMesh(std::shared_ptr<Mesh> _mesh) { myMesh = _mesh; }

        Material * getMaterial(){return material;}
        void setMaterial(Material * _mat){material = _mat;}
    };
}; // namespace OpenEngine

#endif /*MESHRENDERER*/