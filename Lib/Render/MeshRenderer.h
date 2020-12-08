#ifndef MESHRENDERER
#define MESHRENDERER

#include "Renderer.h"

namespace OpenEngine
{
    class Mesh;
    class Shader;
    class Object;
    class Material3D;
    
    class MeshRenderer : public Renderer
    {
    protected:

    public:
        MeshRenderer(Object & object);

        void render() override;
        void prepare() override;
        BaseComponent * instantiate(){return new MeshRenderer(*this);}
    };
}; // namespace OpenEngine

#endif /*MESHRENDERER*/