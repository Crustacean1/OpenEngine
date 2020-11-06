#ifndef CAMERA
#define CAMERA

#include <memory>

namespace glm
{
    class mat4;
    class vec3;
    class vec4;
    class dquat;
};
namespace OpenEngine
{
    class Object;
    class Camera
    {
        std::weak_ptr<Object>  owner;

        glm::mat4 &projMat;
        glm::dquat &viewQuat;
        
        double fov;
        double near;
        double far;
        enum :unsigned int {ORTHOGONAL,PERSPECTIVE} projectionType;

        public:
        Camera(Object * object);

        glm::mat4 & getMatrix(glm::dquat _position);
    };
};

#endif /*CAMERA*/