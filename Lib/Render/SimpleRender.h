#ifndef SIMPLERENDER
#define SIMPLERENDER

#include "Render.h"

namespace OpenEngine
{
    class Camera;
    class SimpleRender : Render
    {
        std::shared_ptr<Camera> mainCamera;
    public:
        SimpleRender(std::shared_ptr<Camera> _cam) : mainCamera(_cam){}
        void render() override;
        void setCamera(const std::shared_ptr<Camera> &_cam){mainCamera=_cam;}
        std::shared_ptr<Camera> getCamera(){return mainCamera;}
    };
}; // namespace OpenEngine

#endif /*SIMPLERENDER*/