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

    template <typename K, typename M>
    class ComponentManager;

    enum SceneState
    {
        Inactive,
        Init,
        Play,
        Pause,
        End
    };

    class Scene //Important notice: order matters, UID should be placed on top of objects which might require it
    {
        std::set<Object *> objects;
        double time1 = 0;
        double time2 = 0;

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

    private:
        BehaviourManager &freud;
        Render3D &picasso;
        PhysicManager &feynman;
    };
}; // namespace OpenEngine

#endif /*SCENE*/