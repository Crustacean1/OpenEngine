#include "Game.h"
#include "../../Main/Fractal/FractalComponent.h"
#include "../Component/BehaviourManager.h"
#include "../../Main/MeshTestObject.h"
#include "../../Main/CameraObject.h"
#include "../Render/MeshRenderer.h"
#include "../Render/SimpleRender.h"
#include "../Material/Material.h"
#include "../Light/PointLight.h"
#include "../Shader/Shader.h"
#include "../Object/Object.h"
#include "../Camera/Camera.h"
#include "../Light/Helios.h"
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
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    //Input Setup

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Mouse::createMouse(window);
    Mouse *mouse = Mouse::getMouse();

    Keyboard::createKeyboard(window);
    Keyboard *keyboard = Keyboard::getKeyboard();

    //Scene Setup

    scenes[1] = std::shared_ptr<Scene>(new Scene);
    currentScene = scenes[1];

    BehaviourManager * bManager = (new BehaviourManager);

    Object *camObj = (new Object());
    auto camControl = camObj->addComponent<CameraControler>();
    //camControl->setManager(bManager.get());
    BasicCamera * mainCamera = camObj->addComponent<BasicCamera>();
    camObj->localPosition = glm::dquat(0,0,1,0);

    camObj->setLocalPosition(glm::vec3(0,0,0));

    mouse->addMovementCallback(camControl);
    SimpleRender * sRender = new SimpleRender(mainCamera);

    currentScene->addComponentManager(bManager);
    currentScene->addComponentManager(sRender);
    currentScene->addComponentManager(sRender->lightManager);

    Shader * shader1 = (new Shader("Shaders/Shader1/shader1.vert", "Shaders/Shader1/shader1.frag"));
    Shader * shader2 = (new Shader("Shaders/Shader2/shader2.vert", "Shaders/Shader2/shader2.frag"));
    Shader * shader3 = (new Shader("Shaders/Shader3/shader3.vert", "Shaders/Shader3/shader3.frag"));
    Shader * shader4 = (new Shader("Shaders/Shader4/shader4.vert", "Shaders/Shader4/shader4.frag"));
    Shader * shader5 = (new Shader("Shaders/Shader5/shader5.vert", "Shaders/Shader5/shader5.frag","Shaders/Shader5/shader5.geom"));

    Material * mat1 = new Material();
    mat1->shader = shader4;
    mat1->diff.loadFromFile("Resources/Images/wall.jpg");
    mat1->diff.flush();
    mat1->spec.loadFromFile("Resources/Images/wall.jpg");
    mat1->spec.flush();
    //mat1->norm.loadFromFile("Resources/Images/awesomeface.png");
    //mat1->norm.createFromColor(128,128,255);
    mat1->norm.flush();

    mat1->shininess = 32.f;

    auto obj2 = new Object();
    auto mRender1 = obj2->addComponent<MeshRenderer>(SimpleMesh<Vertex3p,V2Index>::generateGrid(7,15),nullptr,shader2);
    //mRender1->setManager(sRender.get());
    auto gTemp = obj2->addComponent<GridController>(camObj);
    //gTemp->setManager(bManager.get());
    gTemp->gap = 30.f/6.f;

    //Fractal

    auto light1 = new Object();
    auto pLight = light1->addComponent<PointLight>();
    //pLight->setManager(((SimpleRender*)sRender.get())->lightManager);

    pLight->shader = shader4;
    light1->localPosition = glm::dquat(0,0,0,-5);
    pLight->ambient = 0.02;
    pLight->diffuse = 0.5;
    pLight->specular = 0.25;

    light1->addComponent<MeshRenderer>(SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(15,0.5),nullptr,shader3);

    //auto lamp = new Object();
    //lamp->addChild(light1);
    //lamp->addComponent<RotationController>()->setManager(bManager.get());

    auto fractal = new Object();
    auto mesh1 = SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(45,2);
    mesh1->computeTangentSpace();
    fractal->addComponent<MeshRenderer>(mesh1,mat1,shader4);
    fractal->addComponent<Roughener>();
    //fractal->addComponent<MeshRenderer>(mesh1,nullptr,shader5)->setManager(sRender.get());
    //fractal->addComponent<RotationController>()->setManager(bManager.get());
    //fractal->addComponent<RotationController>()->setManager(bManager.get());
    //fractal->addComponent<FractalComponent>(bManager.get(),sRender.get(),shader3,3)->setManager(bManager.get());
    //fractal->addComponent<MeshRenderer>(SimpleMesh<Vertex3pc,V3Index>::generateSierpinski(10),mat1,shader3)->setManager(sRender.get());
    //std::cout<<fractal->getComponent<FractalComponent>(0)->counter<<std::endl;
    //fractal->addChild(camObj);

    currentScene->add(obj2);
    currentScene->add(fractal);
    currentScene->add(camObj);
    currentScene->add(light1);

    std::cout << "Game loaded\n";
}
void OpenEngine::Game::gameLoop()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    currentScene->loop();
}