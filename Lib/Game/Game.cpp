#include "Game.h"
#include "../Component/BehaviourManager.h"
#include "../../Main/MeshTestObject.h"
#include "../../Main/CameraObject.h"
#include "../Render/MeshRenderer.h"
#include "../Render/SimpleRender.h"
#include "../Shader/Shader.h"
#include "../Object/Object.h"
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

    MeshRenderer *jp2gmd;

    std::cout<<typeid(jp2gmd).name()<<std::endl;

    //Scene Setup

    scenes[1] = std::shared_ptr<Scene>(new Scene);
    currentScene = scenes[1];

    std::shared_ptr<BehaviourManager> bManager(new BehaviourManager);
    std::shared_ptr<BehaviourManager> dummyManager(new BehaviourManager);


    Object *camObj = (new Object());
    CameraControler* camControl = new CameraControler(*camObj,bManager.get());
    BasicCamera * mainCamera = new BasicCamera(*camObj);
    camObj->localPosition = glm::dquat(0,0,1,0);

    camObj->setLocalPosition(glm::vec3(0,0,0));

    mouse->addMovementCallback(camControl);

    currentScene->set(bManager);

    //Object Setup

    std::shared_ptr<Render> sRender((Render *)new SimpleRender(mainCamera));
    currentScene->add(sRender);

    Shader * shader1 = (new Shader("Shaders/Shader1/shader1.vert", "Shaders/Shader1/shader1.frag"));
    Shader * shader2 = (new Shader("Shaders/Shader2/shader2.vert", "Shaders/Shader2/shader2.frag"));
    Shader * shader3 = (new Shader("Shaders/Shader3/shader3.vert", "Shaders/Shader3/shader3.frag"));

    auto obj2 = new Object();
    auto mRender1 = new MeshRenderer(*obj2,SimpleMesh<Vertex3p,V2Index>::generateGrid(7,15),nullptr,shader2);
    mRender1->setManager(sRender.get());
    auto gTemp = new GridController(*obj2,bManager.get(),camObj);
    gTemp->gap = 30.f/6.f;
    //obj2->init(sRender, SimpleMesh<Vertex3p, V2Index>::generateGrid(5, 15), shader2);

    auto obj3 = new Object();
    auto mRender2 = new MeshRenderer(*obj3,SimpleMesh<Vertex3pc,V3Index>::generateSphere(35,1),nullptr,shader3);
    //obj3->init(sRender, SimpleMesh<Vertex3pc, V3Index>::generateSphere(35, 1), shader3);
    mRender2->setManager(sRender.get());
    new RotationController(*obj3,bManager.get(),glm::vec3(1,0,0));
    obj3->localPosition = glm::dquat(0, 0, 0, 30.f/6.f);

    auto obj4 = new Object();
    auto mRender3 = new MeshRenderer(*obj4,SimpleMesh<Vertex3pcn,V3Index>::generateTorus(55,2,0.3),nullptr,shader3);
    mRender3->setManager(sRender.get());
    new RotationController(*obj4,bManager.get(),glm::vec3(0,1,0));
    //obj4->init(sRender, SimpleMesh<Vertex3pcn, V3Index>::generateTorus(55, 2, 0.3), shader3);
    obj4->localPosition = glm::dquat(0, 0, 0, 0);

    auto obj5 = new Object();
    auto mRender4 = new MeshRenderer(*obj5,SimpleMesh<Vertex3pc,V3Index>::generateSphere(30,0.33),nullptr,shader3);
    mRender4->setManager(sRender.get());
    new RotationController(*obj5,bManager.get(),glm::vec3(0,1,0));
    //obj5->init(sRender, SimpleMesh<Vertex3pc, V3Index>::generateSphere(30, 0.33), shader3);
    obj5->localPosition = glm::dquat(0, 1, 1, 1);
    obj5->localScale = glm::dquat(0,2,2,0.5);

    obj4->addChild(obj5);
    obj3->addChild(obj4);

    //obj4->addChild(camObj);

    currentScene->add(obj2);
    //currentScene->add(obj3);
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
    }
}