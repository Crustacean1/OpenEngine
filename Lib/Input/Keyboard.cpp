#include "Keyboard.h"
#include "Input.h"
#include <GLFW/glfw3.h>

OpenEngine::Keyboard *OpenEngine::Keyboard::ptr = nullptr;

using namespace std::placeholders;

OpenEngine::Keyboard *OpenEngine::Keyboard::getKeyboard() { return ptr; }
void OpenEngine::Keyboard::createKeyboard(GLFWwindow *_window)
{
    if (ptr != nullptr)
    {
        return;
    }
    ptr = new Keyboard();
    ptr->window = _window;
    glfwSetCharCallback(_window, charCallbackInvoker);
}
void OpenEngine::Keyboard::keyCallbackInvoker(GLFWwindow *window, unsigned int key, unsigned int scancode, unsigned int action, unsigned int mode)
{
    for (const auto &callback : ptr->keyCallbacks)
    {
        callback->keyCallback(window, key, scancode, action, mode);
    }
}
void OpenEngine::Keyboard::charCallbackInvoker(GLFWwindow *window, unsigned int codepoint)
{
    for (const auto &callback : ptr->charCallbacks)
    {
        callback->charCallback(window, codepoint);
    }
}

void OpenEngine::Keyboard::addKeyCallback(KeyInput *_kinput)
{
    keyCallbacks.push_front(_kinput);
}
void OpenEngine::Keyboard::dropKeyCallback(KeyInput *_kinput)
{
    for (auto it = keyCallbacks.begin(); it != keyCallbacks.end(); it++)
    {
        if ((*it) == _kinput)
        {
            keyCallbacks.erase(it);
            return;
        }
    }
}
void OpenEngine::Keyboard::addCharCallback(CharInput *_kinput)
{
    charCallbacks.push_front(_kinput);
}
void OpenEngine::Keyboard::dropCharCallback(CharInput *_kinput)
{
    for (auto it = charCallbacks.begin(); it != charCallbacks.end(); it++)
    {
        if ((*it) == _kinput)
        {
            charCallbacks.erase(it);
            return;
        }
    }
}