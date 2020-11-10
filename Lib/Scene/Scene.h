#ifndef SCENE
#define SCENE

#include <map>
#include <set>
#include <string>
#include <memory>

namespace OpenEngine
{
    class Object;
    class Render;
    class BehaviourManager;

    class Scene
    {
        std::map<std::string,Object*> objects;
        std::set<std::shared_ptr<Render>> renders;

        std::shared_ptr<BehaviourManager> bManager;

        double time1 =0;
        double time2 =0;
        //Render???
        public:

        void init();

        void add(Object * _object);
        Object * drop(Object * _object);

        void add(std::shared_ptr<Render> _object);
        std::shared_ptr<Render> drop(std::shared_ptr<Render> _object);

        void set(std::shared_ptr<BehaviourManager> _man){bManager = _man;}

        void render();
        void update();

    };
}; // namespace OpenEngine

#endif /*SCENE*/