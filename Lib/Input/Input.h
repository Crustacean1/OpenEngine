#ifndef INPUT
#define INPUT

class GLFWwindow;

namespace OpenEngine
{
    class MouseMovementInput
    {
    public:
        virtual void mouseMovementCallback(GLFWwindow *window, double xpos, double ypos) = 0;
    };
    class MouseButtonInput
    {
    public:
        virtual void mouseButtonCallback(GLFWwindow *window, int button, int action, int mode) = 0;
    };
    class KeyboardInput
    {
    public:
        virtual void keyboardCallback(GLFWwindow *window, int key, int scancode, int action, int mods) = 0;
    };
    class CharInput
    {
    public:
        virtual void charInput(GLFWwindow *window, unsigned int codepoint) = 0;
    };
}; // namespace OpenEngine

#endif /*INPUT*/