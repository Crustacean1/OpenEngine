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
        std::list<KeyInput *> keyCallbacks;
        std::list<CharInput *> charCallbacks; 

        static void charCallbackInvoker(GLFWwindow * window, unsigned int codepoint);
        static void keyCallbackInvoker(GLFWwindow * window,unsigned int key,unsigned int scancode,unsigned int action,unsigned int mode);

        GLFWwindow * window;

        Keyboard(){}
        public:

        static Keyboard * getKeyboard();
        static void createKeyboard(GLFWwindow * _window);

        void addKeyCallback(KeyInput * _minput);
        void dropKeyCallback(KeyInput * _minput);

        void addCharCallback(CharInput * _minput);
        void dropCharCallback(CharInput * _minput);
    };
}; // namespace OpenEngine

#endif /*KEYBOARD*/