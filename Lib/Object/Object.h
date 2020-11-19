#ifndef OBJECT
#define OBJECT

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <string>
#include <map>
#include <set>
#include <list>

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
        Scene * scene = nullptr;

        std::set<Object *> children;
        std::map<std::string, std::list<BaseComponent*>> components;

        glm::dquat globalRotation;
        glm::dquat globalScale;
        glm::dquat globalPosition;

        void updateComponentManagers(Scene * _s);

        // Scale->rotation->translation <- transform order

    public:
        glm::dquat localRotation;
        glm::dquat localScale;
        glm::dquat localPosition;

        Object();
        Object(Object *parent);

        ~Object();
        std::string getId() const;

        Object * find(const std::string &_id);
        Object * drop(const std::string &_id);

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

        void addChild(Object *_child);
        void dropChild(Object *_child);

        template <typename K, typename... Args>
        K* addComponent(Args... args);

        template <typename K>
        void dropComponent(K *_comp);

        template<typename K>
        K * getComponent(unsigned int i);

        template<typename K>
        unsigned int getComponentCount();

        Scene * getScene();
        void setScene(Scene * _s);
        void dropScene();

        //Copy (in future also move) operators <- TODO

        Object &operator()(const Object &_obj);
        Object &operator=(const Object &_obj);

        //Tags (rather not)
        //Add serializable class <- Would require unique indexing???(Or global map from prev memory address to current) Saving pointer links
    };
    template <typename K, typename... Args>
    K * Object::addComponent(Args... args)
    {
        if (components.find(typeid(K).name()) != components.end())
        {
            components[typeid(K).name()].push_back((BaseComponent*)new K(*this,args...));
            return (K*)components[typeid(K).name()].back();
        }
        components[typeid(K).name()] = std::list<BaseComponent*>{(BaseComponent*)new K(*this,args...)};
            return (K*)components[typeid(K).name()].back();
    }
    template <typename K>
    void Object::dropComponent(K *_comp)
    {
        if (components.find(typeid(K).name()) != components.end())
        {
            components[typeid(K).name()].erase(std::find(components[typeid(K).name()],_comp));
        }
    }
    template<typename K>
    K * Object::getComponent(unsigned int i)
    {
        if(components.find(typeid(K).name())!=components.end())
        {
            if(i<components[typeid(K).name()].size())
            {
                auto beg = components[typeid(K).name()].begin();
                std::advance(beg,i);
                return (K*)*beg;
            }
        } 
        return nullptr;
    }
    template<typename K>
    unsigned int Object::getComponentCount()
    {
        if(components.find(typeid(K).name())==components.end())
        {
            return 0;
        }
        return components[typeid(K).name()].size();
    }
}; // namespace OpenEngine

#endif /*OBJECT*/