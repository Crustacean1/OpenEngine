#ifndef CAMERA
#define CAMERA

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "../Component/BaseComponent.h"

namespace OpenEngine
{
    class Object;

    class CameraManager;

    class Camera : public BaseComponent
    {
    public:
        Camera(Object &_obj);
        virtual glm::mat4 getViewMatrix(glm::vec3 _position, glm::dquat rotation, glm::vec3 scale) = 0;
        virtual glm::mat4 getProjectionMatrix() = 0;
        ~Camera() {}
    };

    class BasicCamera : public Camera
    {
        void computeProjectionMatrix();

        glm::mat4 projMat;

        double fov;
        double aspect;
        double near;
        double far;

        enum : unsigned int
        {
            ORTHOGONAL,
            PERSPECTIVE
        } projectionType;

    public:
        BasicCamera(Object &_obj, double _fov = 45, double _aspect = 8.f / 6.f, double _n = 0.1, double _f = 300);

        virtual glm::mat4 getViewMatrix(glm::vec3 _position, glm::dquat rotation, glm::vec3 scale);
        glm::mat4 getProjectionMatrix() { return projMat; }

        void setFov(double _fov) { fov = _fov; }
        void setCutoff(double _n, double _f)
        {
            near = _n;
            far = _f;
        }
        void setAspect(double _aspect) { aspect = _aspect; }

        void setCamera(double _fov, double _aspect, double _n, double _f)
        {
            fov = _fov;
            aspect = _aspect;
            near = _n;
            far = _f;
        }
        BaseComponent *instantiate() override;
    };
}; // namespace OpenEngine

#endif /*CAMERA*/