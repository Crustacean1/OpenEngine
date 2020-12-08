#ifndef SCENE
#define SCENE

#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>
#include "../Utilities/UID/UID.h"

namespace OpenEngine
{
    class Object;
    class Render3D;
    class BehaviourManager;
    class PhysicManager;


    template <typename K,typename M>
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
        std::set<Object *> objects;
        double time1 = 0;
        double time2 = 0;

        BehaviourManager &freud;
        Render3D & picasso;
        PhysicManager & feynman;

        SceneState state;
        //Render???
    public:
        Scene();

        void init();

        void add(Object *_object);
        Object *drop(Object *_object);

        void render();
        void update();
        void loop();

        UID<Scene> uid;
    };
}; // namespace OpenEngine

#endif /*SCENE*/