#include "Window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../Exception/Exception.h"

namespace OpenEngine
{
    Window::Window(int width, int height, const char *name, GLFWmonitor *monitor, GLFWwindow *share)
    {
        init(width, height, name, monitor, share);
    }
    void Window::init(int width, int height, const char *name, GLFWmonitor *monitor, GLFWwindow *share)
    {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(width, height, name, monitor, share);
        if (window == NULL)
        {
            glfwTerminate();
            throw DevException("Failed to create GLFW window");
        }
        glfwMakeContextCurrent(window);
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            glfwTerminate();
            throw DevException("Failed to initialize GLAD");
        }
        glViewport(0, 0, width, height);
        glfwSetFramebufferSizeCallback(window,[](GLFWwindow * win,int width,int height){glViewport(0,0,width,height);});
    }
}; // namespace OpenEngine