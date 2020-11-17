#include "Shader.h"
#include <fstream>
#include <iostream>
#include <glad/glad.h>

unsigned int OpenEngine::Shader::loadSubShader(const char *filename, unsigned int target)
{
    std::fstream file(filename);
    if (!file.is_open())
    {
        throw((std::string) "Could not open shader file: " + filename);
    }
    char *buffer;
    unsigned int length;

    file.seekg(0, file.end);
    length = file.tellg();
    file.seekg(0, file.beg);

    buffer = new char[length + 1];
    file.read(buffer, length);
    buffer[length] = 0;

    unsigned int shader = glCreateShader(target);
    glShaderSource(shader, 1, &buffer, NULL);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, NULL, infoLog);
        throw((std::string)infoLog);
    }
    return shader;
}

void OpenEngine::Shader::load(const char *vs, const char *fs, const char *gs)
{
    ID = glCreateProgram();
    unsigned int shaders[3];
    unsigned int targets[] = {GL_VERTEX_SHADER, GL_FRAGMENT_SHADER, GL_GEOMETRY_SHADER};
    const char *filenames[] = {vs, fs, gs};
    bool bShaders[3] = {false, false, false};

    for (int i = 0; i < 3; i++)
    {
        if (filenames[i][0] == 0)
        {
            continue;
        }
        try
        {
            shaders[i] = loadSubShader(filenames[i], targets[i]);
            bShaders[i] = true;
            glAttachShader(ID, shaders[i]);
        }
        catch (std::string msg)
        {
            std::cout <<"throwin: "<< msg << std::endl;
        }
    }
    glLinkProgram(ID);
    int success;
    char infoLog[512];
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if (!success)
    {
        glGetProgramInfoLog(ID, 512, NULL, infoLog);
        std::cout <<"In shader.cpp: "<< infoLog << std::endl;
        throw "Failed to link shader";
    }
    for (int i = 0; i < 3; i++)
    {
        if (bShaders[i] == true)
        {
            glDeleteShader(shaders[i]);
        }
    }
}
void OpenEngine::Shader::loadUniforms()
{
    GLint count;
    GLint size;
    constexpr GLint bufSize= 32;
    GLenum type;
    GLchar name[bufSize];
    GLsizei length;

    glGetProgramiv(ID,GL_ACTIVE_UNIFORMS,&count);
    for(GLint i = 0;i<count;i++)
    {
        glGetActiveUniform(ID,(GLuint)i,bufSize,&length,&size,&type,name);
        uniforms[name]= glGetUniformLocation(ID,name);
    }
}
OpenEngine::Shader::Shader(const char *vs, const char *fs, const char *gs)
{
    load(vs, fs, gs);
    loadUniforms();
}
void OpenEngine::Shader::use()
{
    glUseProgram(ID);
}

void OpenEngine::Shader::set(std::string name, int var)
{
    if(uniforms.find(name)==uniforms.end()){return;}
    glUniform1i(uniforms[name],var);
}
void OpenEngine::Shader::set(std::string name, float var)
{   
    if(uniforms.find(name)==uniforms.end()){return;}
    glUniform1f(uniforms[name],var);
}
void OpenEngine::Shader::set(std::string name, glm::vec3 var)
{
    if(uniforms.find(name)==uniforms.end()){return;}
    glUniform3fv(uniforms[name],1,glm::value_ptr(var));
}
void OpenEngine::Shader::set(std::string name, glm::vec4 var)
{
    if(uniforms.find(name)==uniforms.end()){return;}
    glUniform4fv(uniforms[name],1,glm::value_ptr(var));
}
void OpenEngine::Shader::set(std::string  name, glm::mat4 var)
{
    if(uniforms.find(name)==uniforms.end()){return;}
    glUniformMatrix4fv(uniforms[name],1,GL_FALSE,glm::value_ptr(var));
}