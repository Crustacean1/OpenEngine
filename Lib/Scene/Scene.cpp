#include "Scene.h"
#include <GLFW/glfw3.h>
#include "../Object/Object.h"
#include "../Render/SimpleRender.h"
#include "../Render/Renderer.h"
#include "../Component/BehaviourManager.h"
#include "../Window/Window.h"

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
    _object->setScene(this);
}
OpenEngine::Object * OpenEngine::Scene::drop(Object * _object)
{
    objects.erase(objects.find(_object->getId()));
}
void OpenEngine::Scene::loop()
{
    time1 = time2 = glfwGetTime();
    auto window = Window::getMainWindow();
    while(state!=SceneState::End&&!glfwWindowShouldClose(window))
    {
        time2 = glfwGetTime();
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        ((BehaviourManager*)managers[BehaviourManager::getTypename()][0])->update(time2-time1);
        ((Render*)managers[Render::getTypename()][0])->render();

        glfwSwapBuffers(window);

        time1 = time2;
    }
}