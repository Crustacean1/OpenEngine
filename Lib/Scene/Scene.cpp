#include "Scene.h"
#include <GLFW/glfw3.h>
#include "../Object/Object.h"
#include "../Render/Render.h"
#include "../Component/BehaviourManager.h"

void OpenEngine::Scene::render()
{
    for (const auto &render : renders)
    {
        render->render();
    }
}
void OpenEngine::Scene::update()
{
    time2 = glfwGetTime();
    bManager->update(time2-time1);
    time1 = time2;
}

void OpenEngine::Scene::init()
{
}
void OpenEngine::Scene::add(Object* _object)
{
    if (objects.find(_object->getId()) != objects.end())
    {
        return;
    }
    objects[_object->getId()] = _object;
}
OpenEngine::Object * OpenEngine::Scene::drop(Object * _object)
{
    objects.erase(objects.find(_object->getId()));
}

void OpenEngine::Scene::add(std::shared_ptr<Render> _object)
{
    renders.insert(_object);
}
std::shared_ptr<OpenEngine::Render> OpenEngine::Scene::drop(std::shared_ptr<Render> _object)
{
    renders.erase(renders.find(_object));
}