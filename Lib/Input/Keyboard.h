#ifndef KEYBOARD
#define KEYBOARD

#include <memory>
#include <list>
#include <functional>

class GLFWwindow;

namespace OpenEngine
{
    class KeyInput;
    class CharInput;
    class Keyboard
    {
        static Keyboard *ptr;
        std::list<std::pair<std::weak_ptr<KeyInput>, std::function<void(double)>>> keyCallbacks;
        std::list<std::pair<std::weak_ptr<CharInput>, std::function<void(GLFWwindow*,unsigned int)>>> charCallbacks; 

        static void charCallbackInvoker(GLFWwindow * window, unsigned int codepoint);

        GLFWwindow * window;

        Keyboard(){}
        public:

        static void keyCallbackInvoker(double delta);

        static Keyboard * getKeyboard();
        static void createKeyboard(GLFWwindow * _window);

        void addKeyCallback(std::shared_ptr<KeyInput> _minput);
        void dropKeyCallback(KeyInput * _minput);

        void addCharCallback(std::shared_ptr<CharInput> _minput);
        void dropCharCallback(CharInput * _minput);
    };
}; // namespace OpenEngine

#endif /*KEYBOARD*/