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
    glfwSetKeyCallback(_window, OpenEngine::Keyboard::keyCallbackInvoker);
    glfwSetCharCallback(_window, charCallbackInvoker);
}
void OpenEngine::Keyboard::keyCallbackInvoker(GLFWwindow *window, int key, int scancode, int action, int mode)
{
    for (const auto &callback : ptr->keyCallbacks)
    {
        callback.second(window, key, scancode, action, mode);
    }
}
void OpenEngine::Keyboard::charCallbackInvoker(GLFWwindow *window, unsigned int codepoint)
{
    for (const auto &callback : ptr->charCallbacks)
    {
        callback.second(window, codepoint);
    }
}

void OpenEngine::Keyboard::addKeyCallback(std::shared_ptr<KeyInput> _kinput)
{
    keyCallbacks.push_front(std::pair<std::shared_ptr<KeyInput>, std::function<void(GLFWwindow *, int, int, int, int)>>(_kinput, std::bind(&KeyInput::keyCallback, _kinput, _1, _2, _3, _4, _5)));
}
void OpenEngine::Keyboard::dropKeyCallback(KeyInput *_kinput)
{
    for (auto it = keyCallbacks.begin(); it != keyCallbacks.end(); it++)
    {
        if((*it).first.lock().get()==_kinput)
        {
            keyCallbacks.erase(it);
            return;
        }
    }
}
void OpenEngine::Keyboard::addCharCallback(std::shared_ptr<CharInput> _kinput)
{
    charCallbacks.push_front(std::pair<std::shared_ptr<CharInput>, std::function<void(GLFWwindow *,unsigned int)>>(_kinput, std::bind(&CharInput::charCallback, _kinput, _1,_2)));
}
void OpenEngine::Keyboard::dropCharCallback(CharInput *_kinput)
{
    for (auto it = charCallbacks.begin(); it != charCallbacks.end(); it++)
    {
        if((*it).first.lock().get()==_kinput)
        {
            charCallbacks.erase(it);
            return;
        }
    }
}