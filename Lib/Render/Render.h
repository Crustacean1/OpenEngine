#ifndef RENDER
#define RENDER

#include <set>
#include <map>
#include <memory>

namespace OpenEngine
{
    class Renderer;
    class Shader;

    class Render
    {
    protected:
        std::map<Shader*, std::set<Renderer *>> renderers;
        void addRenderer(Renderer *_renderer);
        void dropRenderer(Renderer *_renderer);

    public:
        virtual void render() = 0;
        friend Renderer;
    };
}; // namespace OpenEngine

#endif /*RENDER*/