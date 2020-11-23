#include "Game.h"
#include "../../Main/Fractal/FractalComponent.h"
#include "../Component/BehaviourManager.h"
#include "../Light/DirectionalLight.h"
#include "../../Main/MeshTestObject.h"
#include "../../Main/CameraObject.h"
#include "../Render/MeshRenderer.h"
#include "../Render/SimpleRender.h"
#include "../Loaders/MeshLoader.h"
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
    //mat1->norm.loadFromFile("Resources/Models/Model4/body_showroom_ddn.png");
    mat1->norm.createFromColor(4,128,255);
    mat1->norm.flush();

    mat1->shininess = 16.f;
    mat1->update();
    mat1->activate();

    auto obj2 = new Object();
    auto mRender1 = obj2->addComponent<MeshRenderer>(SimpleMesh<Vertex3p,V2Index>::generateGrid(7,15),nullptr,shader2);
    auto gTemp = obj2->addComponent<GridController>(camObj);
    gTemp->gap = 30.f/6.f;

    //Fractal

    auto light1 = new Object();
    light1->addComponent<MeshRenderer>(SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(15,0.5),nullptr,shader3);
    auto pLight = light1->addComponent<PointLight>();

    pLight->shader = shader4;
    light1->localPosition = glm::dquat(0,0,0,-5);

    auto light2 = new Object();
    light2->addComponent<DirectionalLight>(glm::vec3(1,0.8,0.5),0.3f,0.5f,0.75f)->shader = shader4;
    //light2->addComponent<RotationController>();

    auto fractal = new Object();
    auto mesh1 = SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(45,2);
    //mesh1->computeTangentSpace();
    fractal->addComponent<MeshRenderer>(mesh1,mat1,shader4);
    //fractal->addComponent<Roughener>();

    MeshLoader mLoader;
    auto * loadedMesh = mLoader.loadMesh("Resources/Models/2/fan.obj");
    loadedMesh->computeTangentSpace();
    std::cout<<"computed"<<std::endl;
    Object * model = new Object();
    model->addComponent<MeshRenderer>(loadedMesh,mat1,shader4);
    model->addComponent<Roughener>();

    //model->addComponent<MeshRenderer>(loadedMesh,nullptr,shader5);
    model->localScale = glm::dquat(0,0.1,0.1,0.1);
    //model->localRotation = glm::dquat(0,0,sqrt(2)/2,sqrt(2)/2);
    model->localPosition = glm::dquat(0,5,0,0);
    
    currentScene->add(obj2);
    //currentScene->add(fractal);
    currentScene->add(camObj);
    currentScene->add(model);
    currentScene->add(light1);
    currentScene->add(light2);

    std::cout << "Game loaded\n";
}
void OpenEngine::Game::gameLoop()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    currentScene->loop();
}