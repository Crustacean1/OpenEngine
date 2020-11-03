#include "Game.h"
#include <GLFW/glfw3.h>

OpenEngine::Game::Game() : window(*new Window(800,600,"OpenEngine Development"))
{
    initGame();
}

void OpenEngine::Game::initGame()
{
}
void OpenEngine::Game::gameLoop()
{
    while(!glfwWindowShouldClose(window))
    {
        //currentScene->draw();
    }
}