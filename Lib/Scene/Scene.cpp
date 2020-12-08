#include "Scene.h"
#include "../Render/Render.h"
#include "../Physics/Physics.h"
#include <GLFW/glfw3.h>
#include "../Object/Object.h"
#include "../Render/Renderer.h"
#include "../Component/Behaviour/BehaviourManager.h"
#include "../Window/Window.h"
#include <iostream>
#include <fstream>
#include "../../Main/CameraObject.h"
#include "../Input/Mouse.h"

OpenEngine::Scene::Scene() : freud(*new BehaviourManager(this)), picasso(*new Render3D(this,nullptr)), feynman(*new PhysicManager(this))
{

}
void OpenEngine::Scene::init()
{
    auto * camera = new Object(this);
    camera->addComponent<BasicCamera>();
    camera->addComponent<CameraControler>();
    Mouse::getMouse()->addMovementCallback(camera->getComponent<CameraControler>(0));

    picasso.setCamera(camera->getComponent<BasicCamera>(0));


}
void OpenEngine::Scene::add(Object* _object)
{
    if(_object!=nullptr)
    {
        objects.insert(_object);
    }
    _object->setScene(this);
}
OpenEngine::Object * OpenEngine::Scene::drop(Object * _object)
{
    objects.erase(_object);
    return _object;
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

        freud.update(time2-time1);
        feynman.update(time2-time1);
        picasso.render();

        glfwSwapBuffers(window);
        n++;

        time1 = time2;
    }
    deltas<<((float)n)/time1;
    deltas.close();
}