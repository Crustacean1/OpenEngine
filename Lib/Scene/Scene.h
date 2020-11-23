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
    class Render;
    class BehaviourManager;

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
        std::map<std::string, std::vector<void *>> managers;
        double time1 = 0;
        double time2 = 0;

        SceneState state;
        //Render???
    public:
        template <typename T>
        ComponentManager<T> *getComponentManager(unsigned int i);

        void init();

        void add(Object *_object);
        Object *drop(Object *_object);

        template <typename T>
        void addComponentManager(ComponentManager<T> *cManager);

        void render();
        void update();
        void loop();
    };
    template <typename T>
    ComponentManager<T> *Scene::getComponentManager(unsigned int i)
    {
        if (managers.find(ComponentManager<T>::getTypename()) == managers.end())
        {
            return nullptr;
        }
        if (!(i < managers[ComponentManager<T>::getTypename()].size()))
        {
            return nullptr;
        }
        return (ComponentManager<T> *)managers[ComponentManager<T>::getTypename()][i];
    }
    template <typename T>
    void Scene::addComponentManager(ComponentManager<T> *cManager)
    {
        if (managers.find(ComponentManager<T>::getTypename()) == managers.end())
        {
            managers[ComponentManager<T>::getTypename()] = std::vector<void *>{(void *)cManager};
            return;
        }
        managers[ComponentManager<T>::getTypename()].push_back((void*)cManager);
    }
}; // namespace OpenEngine

#endif /*SCENE*/