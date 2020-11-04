#ifndef RENDER
#define RENDER

#include <map>
#include <memory>

class Renderer;

namespace OpenEngine
{
    class Render
    {
        std::map<unsigned int, std::shared_ptr<Renderer>> renderers;
        public:
        virtual void render() = 0;
    };
};

#endif /*RENDER*/