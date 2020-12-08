#ifndef RENDER
#define RENDER

#include <set>
#include <map>
#include <list>
#include "../Mesh/Mesh.h"
#include "../Component/ComponentManager.h"
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

    class Render3D : public ComponentManager<Renderer,Render3D>
    {
        friend Renderer;

    protected:
        Camera *mainCamera;
        InstantiatingBuffer iBuffer;
        std::map<Material *, std::map<Mesh *, std::list<Object *>>> renderees;

        friend ComponentManager<Renderer,Render3D>;
        static std::map<unsigned int,Render3D*> managers;
        //static unsigned int mainIndex;

    public:
        void add(Renderer *_renderer);
        Renderer* drop(Renderer *_renderer);

        Render3D(Scene * _scene, Camera *_cam);
        void setCamera(Camera *_cam) { mainCamera = _cam; }
        Helios *lightManager;
        void render();
        friend Renderer;
    };
}; // namespace OpenEngine

#endif /*RENDER*/