#ifndef RENDER
#define RENDER

#include <set>
#include <map>
#include <memory>
#include "../Component/ComponentManager.h"

namespace OpenEngine
{
    class Renderer;
    class Shader;
    class Camera;

    class Render : public ComponentManager<Renderer>
    {
    protected:
        Camera * mainCamera;
        std::map<Shader*, std::set<Renderer *>> renderers;
        void add(Renderer *_renderer) override;
        void drop(Renderer *_renderer) override;

    public:
        Render(Camera * _cam) : mainCamera(_cam){}
        void setCamera(Camera * _cam){mainCamera = _cam;}
        virtual void render() = 0;
        friend Renderer;
    };
}; // namespace OpenEngine

#endif /*RENDER*/