#include "Game.h"
#include "../../Main/MeshTestObject.h"
#include "../Render/SimpleRender.h"
#include "../Shader/Shader.h"
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
    scenes[1] = std::shared_ptr<Scene>(new Scene);
    currentScene = scenes[1];

    std::shared_ptr<Render> sRender((Render*)new SimpleRender);
    currentScene->add(sRender);

    std::shared_ptr<Shader> shader1(new Shader("Shaders/Shader1/shader1.vert","Shaders/Shader1/shader1.frag"));

    MeshTestObject * obj = new MeshTestObject(std::shared_ptr<Object>(nullptr));
    obj->init(sRender,shader1);

    currentScene->add(std::shared_ptr<Object>((Object*)obj));
    std::cout<<"Game loaded\n";
}
void OpenEngine::Game::gameLoop()
{
    glClearColor(0.5f,0.2f,0.4f,1.f);
    while(!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        currentScene->update();
        currentScene->render();
        glfwSwapBuffers(window);
    }
}