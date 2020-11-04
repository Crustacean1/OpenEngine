#ifndef RENDERER
#define RENDERER

namespace OpenEngine
{
    class Renderer
    {
        public:
        virtual void prepare() = 0;
        virtual void prepareRender() = 0;
    };
}; // namespace OpenEngine

#endif /*RENDERER*/