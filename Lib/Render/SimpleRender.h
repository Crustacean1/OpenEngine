#ifndef SIMPLERENDER
#define SIMPLERENDER

#include "Render.h"

namespace OpenEngine
{
    class BasicCamera;
    class Helios;
    class SimpleRender : Render
    {
    public:
        Helios * lightManager;
        SimpleRender(Camera * _cam);
        void render() override;
    };
}; // namespace OpenEngine

#endif /*SIMPLERENDER*/