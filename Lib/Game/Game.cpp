#include "Game.h"
#include "../Component/BehaviourManager.h"
#include "../../Main/MeshTestObject.h"
#include "../../Main/CameraObject.h"
#include "../Render/SimpleRender.h"
#include "../Shader/Shader.h"
#include "../Camera/Camera.h"
#include "../Input/Mouse.h"
#include "../Mesh/Mesh.h"
#include <GLFW/glfw3.h>
#include <iostream>

OpenEngine::Game::Game() : window(*new Window(800, 600, "OpenEngine Development"))
{
    initGame();
}

void OpenEngine::Game::initGame()
{
}
void OpenEngine::Game::loadGame()
{

    //OpenGL Setup

    glEnable(GL_DEPTH_TEST);

    //Input Setup

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Mouse::createMouse(window);
    Mouse *mouse = Mouse::getMouse();

    Keyboard::createKeyboard(window);
    Keyboard *keyboard = Keyboard::getKeyboard();

    //Scene Setup

    scenes[1] = std::shared_ptr<Scene>(new Scene);
    currentScene = scenes[1];

    CameraObject *camObj = (new CameraObject());
    camObj->init();
    camObj->setLocalPosition(glm::vec3(0, 0, -5));

    mouse->addMovementCallback(camObj->getControler());
    keyboard->addKeyCallback(camObj->getControler());

    std::shared_ptr<BehaviourManager> bManager(new BehaviourManager);
    std::shared_ptr<BehaviourManager> dummyManager(new BehaviourManager);

    currentScene->set(bManager);

    //Object Setup

    std::shared_ptr<Render> sRender((Render *)new SimpleRender(camObj->getCamera()));
    currentScene->add(sRender);

    std::shared_ptr<Shader> shader1(new Shader("Shaders/Shader1/shader1.vert", "Shaders/Shader1/shader1.frag"));
    std::shared_ptr<Shader> shader2(new Shader("Shaders/Shader2/shader2.vert", "Shaders/Shader2/shader2.frag"));
    std::shared_ptr<Shader> shader3(new Shader("Shaders/Shader3/shader3.vert", "Shaders/Shader3/shader3.frag"));

    auto obj = new Object();
    obj->init(sRender, SimpleMesh<Vertex3p, V3Index>::generatePlane(), shader2);

    auto obj2 = new MeshTestObject(*dummyManager);
    obj2->init(sRender, SimpleMesh<Vertex3p, V2Index>::generateGrid(5, 15), shader2);

    auto obj3 = new MeshTestObject(*bManager, glm::vec3(1, 0, 0));
    obj3->init(sRender, SimpleMesh<Vertex3pc, V3Index>::generateSphere(35, 1), shader3);
    obj3->localPosition = glm::dquat(0, 0, 0, 6);

    auto obj4 = new MeshTestObject(*bManager);
    obj4->init(sRender, SimpleMesh<Vertex3pcn, V3Index>::generateTorus(55, 2, 0.3), shader3);
    obj4->localPosition = glm::dquat(0, 0, 0, 0);

    auto obj5 = new MeshTestObject(*bManager, glm::vec3(0, 1, 0));
    obj5->init(sRender, SimpleMesh<Vertex3pc, V3Index>::generateSphere(30, 0.33), shader3);
    obj5->localPosition = glm::dquat(0, 1, 1, 1);
    obj5->localScale = glm::dquat(0,2,2,0.5);

    obj4->addChild(obj5);
    obj3->addChild(obj4);

    currentScene->add(obj);
    currentScene->add(obj2);
    currentScene->add(obj3);
    //currentScene->add(obj4);
    currentScene->add(camObj);
    std::cout << "Game loaded\n";
}
void OpenEngine::Game::gameLoop()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    while (!glfwWindowShouldClose(window))
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