#ifndef OBJECT
#define OBJECT

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include <string>
#include <map>


namespace OpenEngine
{
    class Scene;

    class Object
    {
        //Position, parent , children
        static std::string incrementIndex(std::string &_index);
        static std::string mainIndex;

        const std::string index = incrementIndex(mainIndex);

        std::weak_ptr<Object> parent;

        std::map<std::string, std::shared_ptr<Object>> children;

        glm::dquat localRotation;
        glm::dquat localScale;
        glm::dquat localPosition;

        glm::dquat globalRotation;
        glm::dquat globalScale;
        glm::dquat globalPosition;

        // Scale->rotation->translation
        void flushTransform();

    public:
        Object(std::shared_ptr<Object> _parent);
        std::string getId() const;

        std::shared_ptr<Object> find(const std::string &_id);
        std::shared_ptr<Object> drop(const std::string &_id);

        void add(const std::shared_ptr<Object> & _object);

        //Global state

        glm::dquat getGlobalPosition();
        glm::dquat getGlobalScale();
        glm::dquat getGlobalRotation();

        void rotateGlobal(glm::dquat rotation);
        void translateGlobal(glm::vec3 disp);
        void scaleGlobal(glm::vec3 scale);

        void setGlobalRotation(glm::dquat rotation);
        void setGlobalPosition(glm::vec3 disp);
        void setGlobalScale(glm::vec3 scale);

        //Local state

        glm::dquat getLocalPosition();
        glm::dquat getLocalScale();
        glm::dquat getLocalRotation();
        
        void rotateLocal(glm::dquat rotation);
        void translateLocal(glm::vec3 disp);
        void scaleLocal(glm::vec3 scale);

        void setLocalRotation(glm::dquat rotation);
        void setLocalPosition(glm::vec3 disp);
        void setLocalScale(glm::vec3 scale);

        //global position
        //local position

        //global transform
        //local transform

        //getID
        //Copy/Move constructor
        //Tags (rather not)
        //Add serializable class
        //Will contain Component©
    };
}; // namespace OpenEngine

#endif /*OBJECT*/