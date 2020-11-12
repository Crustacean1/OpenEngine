#ifndef SIMPLERENDER
#define SIMPLERENDER

#include "Render.h"

namespace OpenEngine
{
    class BasicCamera;
    class SimpleRender : Render
    {
    public:
        SimpleRender(Camera * _cam) : Render(_cam){}
        void render() override;
    };
}; // namespace OpenEngine

#endif /*SIMPLERENDER*/