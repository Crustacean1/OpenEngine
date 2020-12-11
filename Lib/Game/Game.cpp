#include "Game.h"
#include "../../Main/Fractal/FractalComponent.h"
#include "../../Main/Labirynth/Cellular.h"
#include "../Component/Behaviour/BehaviourManager.h"
#include "../../Main/Asteroid/Asteroid.h"
#include "../../Main/Compass/Compass.h"
#include "../Light/DirectionalLight.h"
#include "../../Main/MeshTestObject.h"
#include "../../Main/CameraObject.h"
#include "../Render/MeshRenderer.h"
#include "../../Main/Model/Model.h"
#include "../Loaders/MeshLoader/MeshLoader.h"
#include "../Material/Material.h"
#include "../Light/PointLight.h"
#include "../Physics/Physical.h"
#include "../Physics/Physics.h"
#include "../Shader/Shader.h"
#include "../Object/Object.h"
#include "../Camera/Camera.h"
#include "../Render/Render.h"
#include "../Light/Helios.h"
#include "../Input/Mouse.h"
#include "../Mesh/Mesh.h"
#include <GLFW/glfw3.h>
#include <iostream>

OpenEngine::Game::Game() : window(*new Window(800, 600, "OpenEngine Development",glfwGetPrimaryMonitor(),NULL))
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
    glDepthFunc(GL_LEQUAL);
    //glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    //Input Setup

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    Mouse::createMouse(window);
    Mouse *mouse = Mouse::getMouse();

    Keyboard::createKeyboard(window);
    Keyboard *keyboard = Keyboard::getKeyboard();

    //Scene Setup

    scenes[1] = new Scene;
    currentScene = scenes[1];
    currentScene->init();

    Shader * shader1 = (new Shader("Shaders/Shader1/shader1.vert", "Shaders/Shader1/shader1.frag"));
    Shader * shader2 = (new Shader("Shaders/Shader2/shader2.vert", "Shaders/Shader2/shader2.frag"));
    Shader * shader3 = (new Shader("Shaders/Shader3/shader3.vert", "Shaders/Shader3/shader3.frag"));
    Shader * shader4 = (new Shader("Shaders/Shader4/shader4.vert", "Shaders/Shader4/shader4.frag"));
    Shader * shader5 = (new Shader("Shaders/Shader5/shader5.vert", "Shaders/Shader5/shader5.frag","Shaders/Shader5/shader5.geom"));
    Shader * shader6 = (new Shader("Shaders/Shader6/shader6.vert", "Shaders/Shader6/shader6.frag"));

    Material3D * mat2 = new Material3D();
    //Fractal

    auto lamp2 = new Object(currentScene);
    lamp2->transform.localRotation = glm::dquat(-sqrt(2)/2,sqrt(2)/2 ,0,0);
    lamp2->addComponent<DirectionalLight>(glm::vec3(1,1,1),0.2,1.7,1.3)->shader = shader4;

    auto lamp1 = new Object(currentScene);
    lamp1->transform.localRotation = glm::dquat(-0.1,sqrt(0.99) ,0,0);
    lamp1->addComponent<DirectionalLight>(glm::vec3(1,1,1),0.2,0.7,1.3)->shader = shader4;

    auto model = new Object(currentScene);
    model->addComponent<Model>(shader4);
    model->transform.localPosition = glm::dquat(0,0,10,0);

    model->transform.localScale = glm::dquat(0,0.06,0.06,0.06);
    //mouse->addMovementCallback(camObj->addComponent<CameraControler>());
    //camObj->localPosition = glm::dquat(0,0,-4,-8);
    //camObj->localRotation = glm::angleAxis(glm::radians(170.f),glm::vec3(1,0,0));
    //camObj->localScale = glm::dquat(0,5,5,5);
    //model->addChild(camObj);

    //mouse->addMovementCallback(camObj->addComponent<CameraControler>());
    //model->flushTransform();
    //camObj->flushTransform();

    Material3D * fMat = new Material3D();

    CubeMaterial * cmat = new CubeMaterial();
    cmat->cubemap.loadFromFile("Resources/Images/cubemap2/",".png");
    //cmat->cubemap.createFromColor(128,64,64);
    cmat->shader = shader6;

    auto cmap = new Object(currentScene);
    cmap->addComponent<MeshRenderer>()->setMesh(SimpleMesh<Vertex3pntxy,V3Index>::generateCuboid(1,1,1),cmat);

    //auto grid = new Object(currentScene.get());
    //grid->addComponent<MeshRenderer>()->setMesh(SimpleMesh<Vertex3p,V2Index>::generateGrid(11,50),mat2);

    auto physicsTest = new Object(currentScene);
    physicsTest->addComponent<MeshRenderer>()->setMesh(SimpleMesh<Vertex3pntxy,V3Index>::generateCuboid(2,2,2),fMat);
    physicsTest->addComponent<Roughener>();
    physicsTest->transform.localPosition = glm::dquat(0,0,20,0);
    model->addComponent<Physical>(0.1,0.3)->actForce(glm::vec3(1,0,0));

    //camObj->localRotation = glm::dquat(0,0,1,0);
    //grid->addComponent<GridController>(model);

    auto compass = new Object(currentScene);
    compass->addComponent<Compass>();

    auto ast1 = new Object(currentScene);
    ast1->addComponent<AsteroidField>(fMat);

    std::cout << "Game loaded\n";
}
void OpenEngine::Game::gameLoop()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    currentScene->loop();
}