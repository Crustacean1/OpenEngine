#include "Scene.h"
#include "../Render/SimpleRender.h"
#include <GLFW/glfw3.h>
#include "../Object/Object.h"
#include "../Render/Renderer.h"
#include "../Component/BehaviourManager.h"
#include "../Window/Window.h"
#include <iostream>
#include <fstream>

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
    std::ofstream deltas("deltas.txt");
    time1 = time2 = glfwGetTime();
    auto window = Window::getMainWindow();
    int n = 0;
    while(!glfwWindowShouldClose(window))
    {
        time2 = glfwGetTime();
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);

        ((BehaviourManager*)managers[BehaviourManager::getTypename()][0])->update(time2-time1);
        ((Render*)managers[Render::getTypename()][0])->render();

        glfwSwapBuffers(window);
        n++;

        time1 = time2;
    }
    deltas<<((float)n)/time1;
    deltas.close();
}