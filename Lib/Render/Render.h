#ifndef RENDER
#define RENDER

#include <set>
#include <map>
#include "../Mesh/Mesh.h"
#include "../Component/ComponentManager.h"
#include <vector>

namespace OpenEngine
{
    class Renderer;
    class Shader;
    class Material3D;
    class Camera;
    class Object;
    class Mesh;
    
    class InstanceMatrix;

    class InstantiatingBuffer
    {
    public:
        void reallocate();
        Buffer<InstanceMatrix, GL_ARRAY_BUFFER> buff;
    };

    class Render : public ComponentManager<Renderer>
    {
        friend Renderer;

    protected:
        Camera *mainCamera;
        InstantiatingBuffer iBuffer;
        std::map<Material3D *,std::map<Mesh *,std::list<Object *>>> renderees;

        void add(Renderer *_renderer) override;
        void drop(Renderer *_renderer) override;

        std::list<Object *>::iterator add(Material3D *mat, Mesh *_mesh, Object *obj);
        void drop(Material3D *_mat, Mesh *_mesh, std::list<Object *>::iterator it);

    public:
        Render(Camera *_cam) : mainCamera(_cam) {}
        void setCamera(Camera *_cam) { mainCamera = _cam; }
        virtual void render() = 0;
        friend Renderer;
    };
}; // namespace OpenEngine

#endif /*RENDER*/