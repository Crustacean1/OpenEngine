#ifndef WINDOW
#define WINDOW

class GLFWwindow;
class GLFWmonitor;

namespace OpenEngine
{
    class Window
    {
        static Window *mainWindow;
        GLFWwindow *window;

    public:
        Window(int width, int height, const char *name, GLFWmonitor *monitor = 0, GLFWwindow *share = 0);
        void init(int width, int height, const char *name, GLFWmonitor *monitor = 0, GLFWwindow *share = 0);
        Window(GLFWwindow *_win) : window(_win) { mainWindow = this; }
        operator GLFWwindow *() const
        {
            return window;
        }
        static GLFWwindow *getMainWindow() { return ((mainWindow != nullptr) ? (mainWindow->window) : (nullptr)); }
        ~Window();
    };

};     // namespace OpenEngine
#endif /*WINDOW*/