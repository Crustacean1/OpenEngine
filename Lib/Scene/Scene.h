#ifndef SCENE
#define SCENE

#include <map>
#include <set>
#include <list>
#include <string>
#include <memory>

namespace OpenEngine
{
    class Object;
    class Render;
    class BehaviourManager;

    template<typename K>
    class ComponentManager;

    enum SceneState
    {
        Inactive,
        Init,
        Play,
        Pause,
        End
    };

    class Scene
    {
        std::map<std::string,Object*> objects;
        std::map<std::string,std::list<void*>> managers;
        std::set<std::shared_ptr<Render>> renders;

        std::shared_ptr<BehaviourManager> bManager;

        double time1 =0;
        double time2 =0;

        SceneState state;
        //Render???
        public:

        template<typename T>
        ComponentManager<T> * getComponentManager(unsigned int i);

        void init();

        void add(Object * _object);
        Object * drop(Object * _object);

        void add(std::shared_ptr<Render> _object);
        std::shared_ptr<Render> drop(std::shared_ptr<Render> _object);

        void set(std::shared_ptr<BehaviourManager> _man){bManager = _man;}

        void render();
        void update();

    };
    template<typename T>
    T * Scene::getComponentManager(unsigned int i)
    {
        if(managers.find(typeid(T).name())==managers.end()){return nullptr;}
        if(!(i<managers[typeid(T).name()].size())){return nullptr;}
        return (T*)managers[typeid(T).name()][i];
    }
}; // namespace OpenEngine

#endif /*SCENE*/