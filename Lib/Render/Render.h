#ifndef RENDER
#define RENDER

#include <set>
#include <map>
#include "../Mesh/Mesh.h"
#include "../Component/ComponentManager.h"
#include "../Component/ManagerTypes.h"
#include <vector>

namespace OpenEngine
{
    class Renderer;
    class Shader;
    class Material;
    class Camera;
    class Object;
    class Mesh;
    class Helios;

    class InstanceMatrix;

    class InstantiatingBuffer
    {
    public:
        void reallocate(int i);
        Buffer<InstanceMatrix, GL_ARRAY_BUFFER> buff;
    };

    class Render3D : public ComponentManager<Renderer>, public Invariant
    {
        friend Renderer;

    protected:
        Camera *mainCamera;
        InstantiatingBuffer iBuffer;
        std::map<Material *, std::map<Mesh *, std::list<Object *>>> renderees;

    public:
        void add(Renderer *_renderer) override;
        void drop(Renderer *_renderer) override;

        Render3D(Camera *_cam);
        void setCamera(Camera *_cam) { mainCamera = _cam; }
        Helios *lightManager;
        virtual void execute();
        friend Renderer;
    };
}; // namespace OpenEngine

#endif /*RENDER*/