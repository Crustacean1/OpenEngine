#include "Game.h"
#include "../../Main/Fractal/FractalComponent.h"
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

    //Scene Setup

    scenes[1] = std::shared_ptr<Scene>(new Scene);
    currentScene = scenes[1];

    std::shared_ptr<BehaviourManager> bManager(new BehaviourManager);
    std::shared_ptr<BehaviourManager> dummyManager(new BehaviourManager);


    Object *camObj = (new Object());
    CameraControler* camControl = new CameraControler(*camObj);
    camControl->setManager(bManager.get());
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
    auto mRender1 = new MeshRenderer(*obj2,SimpleMesh<Vertex3p,V2Index>::generateGrid(7,15),shader2);
    mRender1->setManager(sRender.get());
    auto gTemp = new GridController(*obj2,camObj);
    gTemp->setManager(bManager.get());
    gTemp->gap = 30.f/6.f;

    //Fractal

    auto fractal = new Object();
    (new MeshRenderer(*fractal,SimpleMesh<Vertex3pc,V3Index>::generateSphere(6,1),shader3))->setManager(sRender.get());
    (new FractalComponent(*fractal,bManager.get(),sRender.get(),shader3,3))->setManager(bManager.get());

    std::cout<<fractal->getComponent<Behaviour>(0)->getTypeName()<<std::endl;

    currentScene->add(obj2);
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