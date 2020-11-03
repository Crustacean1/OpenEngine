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
        glm::vec3 localScale;
        glm::vec3 localPosition;

    public:
        Object(std::shared_ptr<Object> _parent);
        Object(std::shared_ptr<Scene> _parent);
        
        std::string getId() const;

        std::shared_ptr<Object> find(const std::string &_id);
        std::shared_ptr<Object> drop(const std::string &_id);

        void add(std::shared_ptr<Object> _object);

        glm::vec3 getGlobalPosition();
        glm::vec3 getGlobalScale();
        glm::dquat getGlobalRotation();

        glm::vec3 getLocalPosition();
        glm::vec3 getLocalScale();
        glm::dquat getLocalRotation();

        //global position
        //local position

        //global transform
        //local transform

        //getID
        //Copy/Move constructor
        //Tags (rather not)
        //Add serializable class
    };
}; // namespace OpenEngine

#endif /*OBJECT*/