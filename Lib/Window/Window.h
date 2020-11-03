#ifndef WINDOW
#define WINDOW

class GLFWwindow;
class GLFWmonitor;

namespace OpenEngine
{
    class Window
    {
        GLFWwindow *window;
    public:
        Window(int width, int height,const char * name,GLFWmonitor *monitor = 0, GLFWwindow *share = 0);
        void init(int width, int height,const char * name, GLFWmonitor *monitor = 0, GLFWwindow *share = 0);
        Window(GLFWwindow *_win) : window(_win) {}
        operator GLFWwindow *() const
        {
            return window;
        }
    };

};     // namespace OpenEngine
#endif /*WINDOW*/