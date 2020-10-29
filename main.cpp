#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Lib/VAO.h"
#include "Lib/Shader.h"

void framebuffer_size_callback(GLFWwindow * widnow,int width,int height)
{
    glViewport(0,0,width,height);
}

void processInput(GLFWwindow * window)
{
    if(glfwGetKey(window,GLFW_KEY_ESCAPE)==GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window,true);
    }
}

std::ostream &operator<<(std::ostream &stream, OpenEngine::Vertex3p vert)
{
    stream << vert.pos.x << "\t" << vert.pos.y << "\t" << vert.pos.z << " ";
    return stream;
}

int main(int argc, char ** argv)
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,2);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow * window  = glfwCreateWindow(800,600,"OpenEngine",NULL,NULL); // Interesting options
    if(window == NULL)
    {
        std::cout<<"Failed to create GLFW window"<<std::endl;
        glfwTerminate();
        return 0;
    }
    glfwMakeContextCurrent(window);
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout<<" Failed to initialize GLAD"<<std::endl;
        glfwTerminate();
        return 0;
    }
    glViewport(0,0,800,600);
    glfwSetFramebufferSizeCallback(window,framebuffer_size_callback);

    glClearColor(0.2f,0.3f,0.3f,1.0f);

    //Testing area

    Shader shader1("Shaders/shader1.vert","Shaders/shader1.frag");

    OpenEngine::Buffer<unsigned int,GL_ELEMENT_ARRAY_BUFFER> buff1;
    OpenEngine::Buffer<OpenEngine::Vertex3p,GL_ARRAY_BUFFER> buff2;

    OpenEngine::VAO v1;
    v1.swapBuffer(buff1);
    v1.swapBuffer(buff2);

    buff1.setBuffer(std::shared_ptr<unsigned int>(new unsigned int[6]{0,1,2,0,3,2}),6);
    buff1.flush();

    buff2.setBuffer(std::shared_ptr<OpenEngine::Vertex3p>(new OpenEngine::Vertex3p[34]{glm::vec3(-0.5f,0.f,0.f),glm::vec3(0.f,0.75f,0.f),glm::vec3(0.5f,0.f,0),glm::vec3(0.f,-0.75f,0.f)}),4);
    buff2.flush();


    //End of testing area

    while(!glfwWindowShouldClose(window))
    {
        glClear(GL_COLOR_BUFFER_BIT);
        shader1.use();
        v1.bind();
        glDrawElements(GL_TRIANGLES,6,GL_UNSIGNED_INT,0);
        v1.unbind();

        glfwSwapBuffers(window);
        glfwPollEvents();
        processInput(window);
    }
    glfwTerminate();

    return 0;
}