#ifndef SHADER
#define SHADER

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <map>

class Shader
{
    unsigned int ID;
    unsigned int loadSubShader(const char *filename, unsigned int target);
    std::map<std::string,unsigned int> uniforms;

    void loadUniforms();
public:
    Shader();
    Shader(const char *vs = "", const char *fs = "", const char *gs = "");

    void load(const char *vs = "", const char *fs = "", const char *gs = "");
    void use();

    void set(const char * name,int var);
    void set(const char * name,float var);
    void set(const char * name,glm::vec3 var);
    void set(const char * name,glm::vec4 var);
    void set(const char * name,glm::mat4 var);

};

#endif /*SHADER*/