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
        unsigned int mode;

    public:
        MeshRenderer(Object * object, std::shared_ptr<Mesh> _mesh = nullptr, std::shared_ptr<Render> _render = nullptr, std::shared_ptr<Shader> _shader = nullptr);

        void render() override;
        void prepare() override;

        std::shared_ptr<Mesh> getMesh() { return myMesh; }
        void setMesh(std::shared_ptr<Mesh> _mesh) { myMesh = _mesh; }
    };
}; // namespace OpenEngine

#endif /*MESHRENDERER*/