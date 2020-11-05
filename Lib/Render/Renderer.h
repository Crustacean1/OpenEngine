#ifndef RENDERER
#define RENDERER

#include <memory>
class Shader;

namespace OpenEngine
{
    class Renderer
    {
        public:
        virtual void prepare() = 0;
        virtual void prepareRender() = 0;
        virtual std::shared_ptr<Shader> getShader() =0;
    };
}; // namespace OpenEngine

#endif /*RENDERER*/