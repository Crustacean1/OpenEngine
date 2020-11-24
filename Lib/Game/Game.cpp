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
    camObj->localPosition = glm::dquat(0,0,0,0);

    //camObj->setLocalPosition(glm::vec3(0,0,0));

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

    Material * mat2 = new Material();
    mat2->shader = shader4;
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

    auto obj2 = new Object();
    auto mesh2 = SimpleMesh<Vertex3p,V2Index>::generateGrid(10,50);
    obj2->addComponent<MeshRenderer>()->addMesh(mesh2,mat2);
    
    currentScene->add(obj2);
    currentScene->add(fractal);
    currentScene->add(camObj);
    //currentScene->add(model);

    std::cout << "Game loaded\n";
}
void OpenEngine::Game::gameLoop()
{
    glClearColor(0.f, 0.f, 0.f, 1.f);
    currentScene->loop();
}