#include "Game.h"
#include "../../Main/MeshTestObject.h"
#include "../../Main/CameraObject.h"
#include "../Render/SimpleRender.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Input/Mouse.h"
#include "../Mesh/Mesh.h"
#include <GLFW/glfw3.h>
#include <iostream>

OpenEngine::Game::Game() : window(*new Window(800,600,"OpenEngine Development"))
{
    initGame();
}

void OpenEngine::Game::initGame()
{
}
void OpenEngine::Game::loadGame()
{
    glfwSetInputMode(window,GLFW_CURSOR,GLFW_CURSOR_DISABLED);

    glEnable(GL_DEPTH_TEST);

    Mouse::createMouse(window);
    Mouse * mouse = Mouse::getMouse();

    Keyboard::createKeyboard(window);
    Keyboard * keyboard = Keyboard::getKeyboard();

    scenes[1] = std::shared_ptr<Scene>(new Scene);
    currentScene = scenes[1];

    CameraObject * camObj = (new CameraObject(nullptr));
    camObj->init();
    camObj->setLocalPosition(glm::vec3(0,0,-5));

    mouse->addMovementCallback(camObj->getControler());
    keyboard->addKeyCallback(camObj->getControler());

    std::shared_ptr<Render> sRender((Render*)new SimpleRender(camObj->getCamera()));
    currentScene->add(sRender);

    std::shared_ptr<Shader> shader1(new Shader("Shaders/Shader1/shader1.vert","Shaders/Shader1/shader1.frag"));
    std::shared_ptr<Shader> shader2(new Shader("Shaders/Shader2/shader2.vert","Shaders/Shader2/shader2.frag"));
    std::shared_ptr<Shader> shader3(new Shader("Shaders/Shader3/shader3.vert","Shaders/Shader3/shader3.frag"));

    MeshTestObject * obj = new MeshTestObject(std::shared_ptr<Object>(nullptr));
    obj->init(sRender,SimpleMesh<Vertex3p,V3Index>::generatePlane(),shader2);

    MeshTestObject * obj2(new MeshTestObject(std::shared_ptr<Object>(nullptr)));
    obj2->init(sRender,SimpleMesh<Vertex3p,V2Index>::generateGrid(5,15),shader2);

    MeshTestObject * obj3(new MeshTestObject(std::shared_ptr<Object>(nullptr)));
    obj3->init(sRender,SimpleMesh<Vertex3pc,V3Index>::generateSphere(25,3),shader3);
    obj3->localPosition = glm::dquat(0,0,0,6);

    MeshTestObject * obj4(new MeshTestObject(std::shared_ptr<Object>(nullptr)));
    obj4->init(sRender,SimpleMesh<Vertex3pcn,V3Index>::generateTorus(35,5,0.2),shader3);
    obj4->localPosition = glm::dquat(0,0,0,-6);

    currentScene->add(std::shared_ptr<Object>((Object*)obj));
    currentScene->add(std::shared_ptr<Object>((Object*)obj2));
    currentScene->add(std::shared_ptr<Object>((Object*)obj3));
    currentScene->add(std::shared_ptr<Object>((Object*)obj4));
    currentScene->add(std::shared_ptr<Object>(camObj));
    std::cout<<"Game loaded\n";
}
void OpenEngine::Game::gameLoop()
{
    glClearColor(0.f,0.f,0.f,1.f);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        glClear(GL_DEPTH_BUFFER_BIT);
        currentScene->update();
        currentScene->render();
        glfwSwapBuffers(window);
        Keyboard::keyCallbackInvoker(0.02);
    }
}