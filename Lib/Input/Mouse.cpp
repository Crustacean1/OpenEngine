#include "Mouse.h"
#include "Input.h"
#include <GLFW/glfw3.h>

OpenEngine::Mouse *OpenEngine::Mouse::ptr = nullptr;

using namespace std::placeholders;

void OpenEngine::Mouse::createMouse(GLFWwindow *_window)
{
    if (ptr != nullptr)
    {
        return;
    }
    ptr = new Mouse();
    glfwSetCursorPosCallback(_window, Mouse::movementCallbackInvoker);
    glfwSetMouseButtonCallback(_window, Mouse::buttonCallbackInvoker);
    glfwSetScrollCallback(_window,Mouse::scrollCallbackInvoker);
}
void OpenEngine::Mouse::movementCallbackInvoker(GLFWwindow *_window, double x, double y)
{
    for (const auto &func : ptr->movementCallbacks)
    {
        func->mouseMovementCallback(_window, x, y);
    }
}
void OpenEngine::Mouse::buttonCallbackInvoker(GLFWwindow *_window, int button, int action, int mode)
{
    for (const auto &func : ptr->buttonCallbacks)
    {
        func->mouseButtonCallback(_window, button, action, mode);
    }
}
void OpenEngine::Mouse::scrollCallbackInvoker(GLFWwindow * _window,double x,double y)
{
    for (const auto &func : ptr->scrollCallbacks)
    {
        func->mouseScrollCallback(_window,x,y);
    }
}

void OpenEngine::Mouse::addMovementCallback(MouseMovementInput * _minput)
{
    movementCallbacks.push_front(_minput);
}
void OpenEngine::Mouse::dropMovementCallback(MouseMovementInput *_minput)
{
    for (auto it = movementCallbacks.begin(); it != movementCallbacks.end(); it++)
    {
        if ((*it) == _minput)
        {
            movementCallbacks.erase(it);
            return;
        }
    }
}

void OpenEngine::Mouse::addButtonCallback(MouseButtonInput * _minput)
{
    buttonCallbacks.push_front(_minput);
}
void OpenEngine::Mouse::dropButtonCallback(MouseButtonInput *_minput)
{
    for (auto it = buttonCallbacks.begin(); it != buttonCallbacks.end(); it++)
    {
        if ((*it) == _minput)
        {
            buttonCallbacks.erase(it);
            return;
        }
    }
}
void OpenEngine::Mouse::addScrollCallback(MouseScrollInput * _minput)
{
    scrollCallbacks.push_front(_minput);
}
void OpenEngine::Mouse::dropScrollCallback(MouseScrollInput *_minput)
{
    for (auto it = scrollCallbacks.begin(); it != scrollCallbacks.end(); it++)
    {
        if ((*it) == _minput)
        {
            scrollCallbacks.erase(it);
            return;
        }
    }
}
OpenEngine::Mouse * OpenEngine::Mouse::getMouse(){return ptr;}
OpenEngine::Mouse::Mouse(){}