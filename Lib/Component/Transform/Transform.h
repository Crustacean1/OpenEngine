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
        glm::dquat globalRotation = glm::dquat(1,0,0,0);
        glm::dquat globalScale = glm::dquat(0,1,1,1);
        glm::dquat globalPosition = glm::dquat(0,0,0,0);
        // Scale->rotation->translation <- transform order

    public:
        Transform(Object & _obj);

        glm::dquat localRotation = glm::dquat(1,0,0,0);
        glm::dquat localScale = glm::dquat(0,1,1,1);
        glm::dquat localPosition = glm::dquat(0,0,0,0);
        
        //Global transform

        glm::vec3 getGlobalPosition();
        glm::vec3 getGlobalScale();
        glm::dquat getGlobalRotation();

        void setGlobalRotation(glm::dquat rotation);
        void setGlobalPosition(glm::vec3 disp);
        void setGlobalScale(glm::vec3 scale);

        glm::dquat transformVector(glm::vec3 vec);
        glm::dquat transformPosition(glm::vec3 vec);

        void flushTransform();
        BaseComponent* instantiate(){return new Transform(*this);}
        //Copy (in future also move) operators <- TODO
    };
}; // namespace OpenEngine

#endif /*TRANSFORM*/