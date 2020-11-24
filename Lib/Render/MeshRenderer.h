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

    public:
        MeshRenderer(Object & object);

        void render() override;
        void prepare() override;
    };
}; // namespace OpenEngine

#endif /*MESHRENDERER*/