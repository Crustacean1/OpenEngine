#include "Cubemap.h"
#include "../Shader/Shader.h"
#include "../Ext/stb_image.h"
#include <glad/glad.h>
#include <iostream>

unsigned int OpenEngine::Cubemap::mainUnit = 0;
const char *OpenEngine::Cubemap::faces[6] = {"right", "left", "top", "bottom", "front", "back"};

OpenEngine::Cubemap::Cubemap() : texUnit((mainUnit++) % 16)
{
}
OpenEngine::Cubemap::Cubemap(const std::string &filename, const std::string &ext) : Cubemap()
{
    loadFromFile(filename, ext);
}
OpenEngine::Cubemap::Cubemap(unsigned char r, unsigned char g, unsigned char b) : Cubemap()
{
    createFromColor(r, g, b);
}
void OpenEngine::Cubemap::generate()
{
    glGenTextures(1, &textureID);
    bind();
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
void OpenEngine::Cubemap::bind()
{
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
}

bool OpenEngine::Cubemap::loadFromFile(const std::string &dirname, const std::string &extension)
{
    generate();
    int width, height, channels;
    unsigned char *data;
    for (int i = 0; i < 6; i++)
    {
        data = stbi_load((dirname + "/" + faces[i] + extension).c_str(), &width, &height, &channels, 0);
        if (!data)
        {
            return false;
        }
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height,
                     0, GL_RGB, GL_UNSIGNED_BYTE, data);
        stbi_image_free(data);
    }
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}
void OpenEngine::Cubemap::createFromColor(unsigned char r, unsigned char g, unsigned char b)
{
    generate();
    unsigned char data[] = {r, g, b};
    for (int i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, 1, 1,
                     0, GL_RGB, GL_UNSIGNED_BYTE, data);
    }

    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}