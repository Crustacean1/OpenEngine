#ifndef OBJECT
#define OBJECT

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <memory>
#include <string>
#include <map>
#include <set>

namespace OpenEngine
{
    class Scene;
    class BaseComponent;

    class Object final
    {
        static std::string incrementIndex(std::string &_index);
        static std::string mainIndex;

        const std::string index = incrementIndex(mainIndex);

        Object *parent = nullptr;

        std::set<Object *> children;
        std::set<BaseComponent *> components;

        glm::dquat globalRotation;
        glm::dquat globalScale;
        glm::dquat globalPosition;

        // Scale->rotation->translation <- transform order

    public:
        glm::dquat localRotation;
        glm::dquat localScale;
        glm::dquat localPosition;

        Object();
        Object(Object * parent);
        Object(std::set<BaseComponent*> & _compMap);

        ~Object();
        std::string getId() const;

        std::shared_ptr<Object> find(const std::string &_id);
        std::shared_ptr<Object> drop(const std::string &_id);

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

        void setLocalRotation(glm::dquat rotation);
        void setLocalPosition(glm::vec3 disp);
        void setLocalScale(glm::vec3 scale);

        void flushTransform();

        //Access regulating functions

        void addChild(Object * _child);
        Object * dropChild(Object * _child);

        void addComponent(BaseComponent * _comp);
        BaseComponent * dropComponent(BaseComponent * _comp);

        //Copy (in future also move) operators <- TODO

        Object & operator()(const Object & _obj);
        Object & operator=(const Object & _obj);

        //Tags (rather not)
        //Add serializable class <- Would require unique indexing???(Or global map from prev memory address to current) Saving pointer links
    };
}; // namespace OpenEngine

#endif /*OBJECT*/