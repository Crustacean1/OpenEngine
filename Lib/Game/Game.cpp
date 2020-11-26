#include "Game.h"
#include "../../Main/Fractal/FractalComponent.h"
#include "../../Main/Labirynth/Cellular.h"
#include "../Component/BehaviourManager.h"
#include "../Light/DirectionalLight.h"
#include "../../Main/MeshTestObject.h"
#include "../../Main/CameraObject.h"
#include "../Render/MeshRenderer.h"
#include "../Render/SimpleRender.h"
#include "../../Main/Model/Model.h"
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
    //auto camControl = camObj->addComponent<CameraControler>();
    BasicCamera * mainCamera = camObj->addComponent<BasicCamera>();
    camObj->localPosition = glm::dquat(0,0,0,0);

    //camObj->setLocalPosition(glm::vec3(0,0,0));

    SimpleRender * sRender = new SimpleRender(mainCamera);

    currentScene->addComponentManager(bManager);
    currentScene->addComponentManager(sRender);
    currentScene->addComponentManager(sRender->lightManager);

    Shader * shader1 = (new Shader("Shaders/Shader1/shader1.vert", "Shaders/Shader1/shader1.frag"));
    Shader * shader2 = (new Shader("Shaders/Shader2/shader2.vert", "Shaders/Shader2/shader2.frag"));
    Shader * shader3 = (new Shader("Shaders/Shader3/shader3.vert", "Shaders/Shader3/shader3.frag"));
    Shader * shader4 = (new Shader("Shaders/Shader4/shader4.vert", "Shaders/Shader4/shader4.frag"));
    Shader * shader5 = (new Shader("Shaders/Shader5/shader5.vert", "Shaders/Shader5/shader5.frag","Shaders/Shader5/shader5.geom"));

    Material3D * mat1 = new Material3D();
    mat1->shader = shader4;

    mat1->amb.loadFromFile("Resources/Images/wall.jpg");
    mat1->amb.flush();
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

    Material3D * mat2 = new Material3D();
    mat2->shader = shader2;
    mat2->amb.createFromColor(255,255,255);
    mat2->amb.flush();
    mat2->diff.createFromColor(255,255,255);
    mat2->diff.flush();
    mat2->spec.createFromColor(255,255,255);
    mat2->spec.flush();
    mat2->update();
    mat2->activate();

    //Fractal

    auto fractal = new Object();
    auto mesh1 = SimpleMesh<Vertex3pntxy,V3Index>::generateSphere(45,2);
    //mesh1->computeTangentSpace();
    fractal->addComponent<MeshRenderer>();
    auto renderer1 = fractal->getComponent<MeshRenderer>(0);
    if(renderer1!=nullptr)
    {
        renderer1->addMesh(mesh1,mat1);
    }
    fractal->localScale = glm::dquat(0,10,10,10);
    fractal->localPosition = glm::dquat(0,0,-20,0);
    fractal->addComponent<Roughener>();

    auto obj2 = new Object();
    auto mesh2 = SimpleMesh<Vertex3p,V2Index>::generateGrid(10,50);
    obj2->addComponent<MeshRenderer>()->addMesh(mesh2,mat2);

    auto lamp1 = new Object();
    lamp1->addComponent<DirectionalLight>(glm::vec3(0.6,0.6,0.6),0.5f,3.3,0.5)->shader = shader4;

    auto lamp2 = new Object();
    lamp2->localRotation = glm::dquat(-sqrt(3)/2,0.5,0,0);
    lamp2->addComponent<DirectionalLight>(glm::vec3(1,1,1),0.2,1.7,0.3)->shader = shader4;

    auto model = new Object();
    model->addComponent<Model>(shader4);

    model->localScale = glm::dquat(0,0.1,0.1,0.1);

    mouse->addMovementCallback(camObj->addComponent<CameraControler>());
    //model->flushTransform();
    //camObj->flushTransform();

    Material3D * fMat = new Material3D();
    fMat->diff.createFromColor(24,24,24);
    fMat->diff.flush();
    fMat->amb.createFromColor(24,24,24);
    fMat->amb.flush();
    fMat->spec.createFromColor(24,24,24);
    fMat->spec.flush();
    fMat->shader = shader4;
    auto floor = new Object();
    floor->addComponent<MeshRenderer>()->addMesh(SimpleMesh<Vertex3pntxy,V3Index>::generateCuboid(50,1,50),fMat);
    floor->addComponent<Roughener>();
    floor->localPosition = glm::dquat(0,0,-1,0);

    auto block = new Object();
    block->addComponent<MeshRenderer>()->addMesh(SimpleMesh<Vertex3pntxy,V3Index>::generateCuboid(0.5,1,0.5),fMat);
    block->localPosition = glm::dquat(0,0,1,0);

    auto lab = new Object();
    lab->addComponent<Labirynth>(mat1,100,100,4,3,1,0.6f);
    lab->addComponent<Roughener>();
    lab->localPosition = glm::dquat(0,-50,0.01,-50);


    //currentScene->add(lamp1);
    currentScene->add(lamp2);
    currentScene->add(model);
    currentScene->add(floor);
    currentScene->add(lab);
    currentScene->add(camObj);

    std::cout << "Game loaded\n";
}
void OpenEngine::Game::gameLoop()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    currentScene->loop();
}