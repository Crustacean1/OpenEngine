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
    glfwSetMouseButtonCallback(_window, buttonCallbackInvoker);
}
void OpenEngine::Mouse::movementCallbackInvoker(GLFWwindow *_window, double x, double y)
{
    for (const auto &func : ptr->movementCallbacks)
    {
        func.second(_window, x, y);
    }
}
void OpenEngine::Mouse::buttonCallbackInvoker(GLFWwindow *_window, int button, int action, int mode)
{
    for (const auto &func : ptr->buttonCallbacks)
    {
        func.second(_window, button, action, mode);
    }
}

void OpenEngine::Mouse::addMovementCallback(std::shared_ptr<MouseMovementInput> _minput)
{
    movementCallbacks.push_front(
        std::pair<std::shared_ptr<MouseMovementInput>, std::function<void(GLFWwindow *, double, double)>>
        (_minput, std::bind(&MouseMovementInput::mouseMovementCallback, _minput, _1, _2, _3)));
}
void OpenEngine::Mouse::dropMovementCallback(MouseMovementInput *_minput)
{
    for (auto it = movementCallbacks.begin(); it != movementCallbacks.end(); it++)
    {
        if ((*it).first.lock().get() == _minput)
        {
            movementCallbacks.erase(it);
            return;
        }
    }
}

void OpenEngine::Mouse::addButtonCallback(std::shared_ptr<MouseButtonInput> _minput)
{
    buttonCallbacks.push_front(
        std::pair<std::shared_ptr<MouseButtonInput>, std::function<void(GLFWwindow *, int, int, int)>>
        (_minput, std::bind(&MouseButtonInput::mouseButtonCallback, _minput, _1, _2, _3, _4)));
}
void OpenEngine::Mouse::dropButtonCallback(MouseButtonInput *_minput)
{
    for (auto it = buttonCallbacks.begin(); it != buttonCallbacks.end(); it++)
    {
        if ((*it).first.lock().get() == _minput)
        {
            buttonCallbacks.erase(it);
            return;
        }
    }
}
OpenEngine::Mouse * OpenEngine::Mouse::getMouse(){return ptr;}
OpenEngine::Mouse::Mouse(){}