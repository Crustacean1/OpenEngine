#ifndef SCENE
#define SCENE

#include <map>
#include <set>
#include <vector>
#include <string>
#include <memory>

namespace OpenEngine
{
    class Object;
    class Render3D;
    class BehaviourManager;

    class Temporal;
    class Invariant;
    class Passive;

    template <typename K>
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
        std::map<std::string, Object *> objects;
        std::map<std::string, Temporal *> tManagers;
        std::map<std::string, Invariant *> iManagers;
        std::map<std::string, Passive *> pManagers;
        double time1 = 0;
        double time2 = 0;

        SceneState state;
        //Render???
    public:
        template <typename T>
        T *getComponentManager();

        void init();

        void add(Object *_object);
        Object *drop(Object *_object);

        template <typename T>
        void addComponentManager(T *cManager);

        void render();
        void update();
        void loop();
    };
    template <typename T>
    T *Scene::getComponentManager()
    {
        if (pManagers.find(typeid(T).name()) == pManagers.end())
        {
            if (iManagers.find(typeid(T).name()) == iManagers.end())
            {
                if (tManagers.find(typeid(T).name()) == tManagers.end())
                {
                    return nullptr;
                }
                return (T *)tManagers[typeid(T).name()];
            }
            return (T *)iManagers[typeid(T).name()];
        }
        return (T *)pManagers[typeid(T).name()];
    }
    template <typename T>
    void Scene::addComponentManager(T *cManager)
    {
        if constexpr (std::is_base_of<Temporal, T>::value)
        {
            if (tManagers.find(typeid(T).name()) == tManagers.end())
            {
                tManagers[typeid(T).name()] = cManager;
                return;
            }
        }
        if constexpr (std::is_base_of<Invariant, T>::value)
        {
            if (iManagers.find(typeid(T).name()) == iManagers.end())
            {
                iManagers[typeid(T).name()] = cManager;
                return;
            }
        }
        if constexpr (std::is_base_of<Passive, T>::value)
        {
            if (pManagers.find(typeid(T).name()) == pManagers.end())
            {
                pManagers[typeid(T).name()] = cManager;
                return;
            }
        }
    }
}; // namespace OpenEngine

#endif /*SCENE*/