#ifndef MOUSE
#define MOUSE

#include <list>
#include <memory>
#include <functional>

class GLFWwindow;

namespace OpenEngine
{
    class MouseButtonInput;
    class MouseMovementInput;
    class Mouse
    {
        static Mouse *ptr;
        std::list<std::pair<std::weak_ptr<MouseMovementInput>, std::function<void(GLFWwindow*,double,double)>>> movementCallbacks;
        std::list<std::pair<std::weak_ptr<MouseButtonInput>, std::function<void(GLFWwindow*,int,int,int)>>> buttonCallbacks;
        Mouse();

        static void movementCallbackInvoker(GLFWwindow * window,double x,double y);
        static void buttonCallbackInvoker(GLFWwindow * window, int button,int action,int mode);

    public:
        static Mouse *getMouse();
        static void createMouse(GLFWwindow *_window);

        void addMovementCallback(std::shared_ptr<MouseMovementInput> _minput);
        void dropMovementCallback(MouseMovementInput * _minput);

        void addButtonCallback(std::shared_ptr<MouseButtonInput> _minput);
        void dropButtonCallback(MouseButtonInput * _minput);
    };
}; // namespace OpenEngine

#endif /*MOUSE*/