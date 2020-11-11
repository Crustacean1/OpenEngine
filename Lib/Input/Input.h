#ifndef INPUT
#define INPUT

#include "Mouse.h"
#include "Keyboard.h"
#include "../Component/Component.h"

class GLFWwindow;

namespace OpenEngine
{
    class MouseMovementInput :public BaseComponent
    {
    public:
        virtual void mouseMovementCallback(GLFWwindow *window, double xpos, double ypos) = 0;
        ~MouseMovementInput(){Mouse::getMouse()->dropMovementCallback(this);}
    };
    class MouseButtonInput : public BaseComponent
    {
    public:
        virtual void mouseButtonCallback(GLFWwindow *window, int button, int action, int mode) = 0;
        ~MouseButtonInput(){Mouse::getMouse()->dropButtonCallback(this);}
    };
    class KeyInput : public BaseComponent
    {
    public:
        virtual void keyCallback(GLFWwindow * window,double delta) = 0;
    };
    class CharInput : public BaseComponent
    {
    public:
        virtual void charCallback(GLFWwindow *window, unsigned int codepoint) = 0;
    };
}; // namespace OpenEngine

#endif /*INPUT*/