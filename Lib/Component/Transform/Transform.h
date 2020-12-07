#ifndef TRANSFORM
#define TRANSFORM

#include "../BaseComponent.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace OpenEngine
{
    class Object;
    class Transform : public BaseComponent
    {
        glm::dquat globalRotation;
        glm::dquat globalScale;
        glm::dquat globalPosition;
        // Scale->rotation->translation <- transform order

    public:
        Transform(Object & _obj);

        glm::dquat localRotation;
        glm::dquat localScale;
        glm::dquat localPosition;
        //Global transform

        glm::vec3 getGlobalPosition();
        glm::vec3 getGlobalScale();
        glm::dquat getGlobalRotation();

        void rotateGlobal(glm::dquat rotation);
        void translateGlobal(glm::vec3 disp);
        void scaleGlobal(glm::vec3 scale);

        void setGlobalRotation(glm::dquat rotation);
        void setGlobalPosition(glm::vec3 disp);
        void setGlobalScale(glm::vec3 scale);

        //Local transform

        glm::vec3 getLocalPosition();
        glm::vec3 getLocalScale();
        glm::dquat getLocalRotation();

        void flushTransform();
        //Copy (in future also move) operators <- TODO
    };
}; // namespace OpenEngine

#endif /*TRANSFORM*/