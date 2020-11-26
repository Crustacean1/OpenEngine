#define STB_IMAGE_IMPLEMENTATION
#include "../Ext/stb_image.h"

#include "Texture.h"
#include <glad/glad.h>
#include <iostream>


unsigned int OpenEngine::Texture2D::mainUnit = GL_TEXTURE0;

OpenEngine::Texture2D::Texture2D() : texUnit(mainUnit = (mainUnit+1)%16){generate();}//To be changed

void OpenEngine::Texture2D::loadFromFile(const std::string & filename)
{
    data = stbi_load(filename.c_str(),&width,&height,&stride,0);
    innerFormat = (stride==3) ? GL_RGB : GL_RGBA;
}
void OpenEngine::Texture2D::generate()
{
    glGenTextures(1,&textureID);
    bind();
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
}
void OpenEngine::Texture2D::bind()
{
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D,textureID);
}
void OpenEngine::Texture2D::flush()
{
    bind();
    glTexImage2D(GL_TEXTURE_2D,0,innerFormat,width,height,0,innerFormat,GL_UNSIGNED_BYTE,data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
OpenEngine::Texture2D::Texture2D(const std::string & filename)
{
    generate();
    loadFromFile(filename);
    flush();
}
OpenEngine::Texture2D::Texture2D(unsigned char r,unsigned char g,unsigned char b)
{
    generate();
    createFromColor(r,g,b);
    flush();
}
void OpenEngine::Texture2D::createFromColor(unsigned char r,unsigned char g,unsigned char b)
{
    width = height = 1;
    data = new unsigned char[3];
    data[0] = r;
    data[1] = g;
    data[2] = b;
    innerFormat = GL_RGB;
}
void OpenEngine::Texture2D::create(int x,int y, char channels)
{
    if(data!=nullptr)
    {
        delete[] data;
    }
    data = new unsigned char[x*y*channels];
    width = x;
    height = y;
    stride = channels;
    innerFormat =  (stride==3) ? GL_RGB : GL_RGBA;
}

