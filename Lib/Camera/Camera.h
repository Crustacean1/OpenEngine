#ifndef CAMERA
#define CAMERA

#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace OpenEngine
{
    class Object;
    class Camera
    {
        void computeProjectionMatrix();

        Object *  owner;

        glm::mat4 &projMat;
        
        double fov;
        double aspect;
        double near;
        double far;

        enum :unsigned int {ORTHOGONAL,PERSPECTIVE} projectionType;

        public:
        Camera(Object * object,double _fov = 45,double _aspect = 1,double _n = 0.1,double _f = 100);

        glm::mat4  getMatrix(glm::vec3 _position,glm::dquat rotatation,glm::vec3 scale);

        void setFov(double _fov){fov = _fov;}
        void setCutoff(double _n,double _f){near = _n;far = _f;}
        void setAspect(double _aspect){aspect = _aspect;}

        void setCamera(double _fov,double _aspect,double _n,double _f)
        {
            fov = _fov;
            aspect = _aspect;
            near = _n;
            far = _f;
        }

    };
};

#endif /*CAMERA*/