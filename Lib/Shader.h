#ifndef SHADER
#define SHADER

class Shader
{
    unsigned int ID;
    unsigned int loadSubShader(const char *filename, unsigned int target);
public:
    Shader();
    Shader(const char *vs = "", const char *fs = "", const char *gs = "");

    void load(const char *vs = "", const char *fs = "", const char *gs = "");
    void use();
};

#endif /*SHADER*/