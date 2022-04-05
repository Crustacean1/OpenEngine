#ifndef OBJECT
#define OBJECT

#include <string>
#include <map>
#include <set>
#include <list>
#include "../Component/Transform/Transform.h"
#include <typeinfo>

namespace OpenEngine
{
    class Scene;

    class BaseComponent;
    template<typename T,typename M>
    class Component;

    class Object final
    {
        friend BaseComponent;

        Object *parent = nullptr;
        Scene *scene = nullptr;

        std::set<Object *> children;
        std::map<std::string, std::list<BaseComponent *>> components;

        void dropComponent(const std::list<BaseComponent *>::iterator &it);

        // Scale->rotation->translation <- transform order

    public:
        Transform transform;

        Object(const Object &_obj);
        Object(Object &&_obj);
        Object(Scene *_scene);
        Object(Object *parent);

        ~Object();

        void addChild(Object *_child);
        void dropChild(Object *_child);

        template <typename K, typename... Args>
        K *addComponent(Args... args);

        template <typename K>
        void dropComponent(K *_comp);

        template <typename K>
        K *getComponent(unsigned int i);

        template <typename K>
        unsigned int getComponentCount();

        Scene *getScene();
        void setScene(Scene *_s);
        void dropScene();

        Object *getParent() { return parent; }
        std::set<Object *> &getChildren() { return children; }

        //Copy (in future also move) operators <- TODO
        Object &operator=(const Object &_obj); // Ultra important!!!!

        //Tags (rather not)
        //Add serializable class <- Would require unique indexing???(Or global map from prev memory address to current) Saving pointer links
    };

    //
    //               Template Implementation below
    //

    template <typename K, typename... Args>
    K* Object::addComponent(Args... args)
    {
        K *ptr = new K(*this, args...);
        components[typeid(K).name()].push_back((BaseComponent *)ptr);
        ptr->setManagerInstance(0);
        return (K *)components[typeid(K).name()].back();
    }

    template <typename K>
    void Object::dropComponent(K *_comp)
    {
        if (components.find(typeid(K).name()) != components.end())
        {
            components[typeid(K).name()].erase(std::find(components[typeid(K).name()], _comp));
        }
    }
    template <typename K>
    K *Object::getComponent(unsigned int i)
    {
        if (components.find(typeid(K).name()) != components.end())
        {
            if (i < components[typeid(K).name()].size())
            {
                auto beg = components[typeid(K).name()].begin();
                std::advance(beg, i);
                return (K *)*beg;
            }
        }
        return nullptr;
    }
    template <typename K>
    unsigned int Object::getComponentCount()
    {
        if (components.find(typeid(K).name()) == components.end())
        {
            return 0;
        }
        return components[typeid(K).name()].size();
    }
}; // namespace OpenEngine

#endif /*OBJECT*/
