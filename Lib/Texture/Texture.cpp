#include <glad/glad.h>
#include "Texture.h"
#include "../Loaders/TextureLoader/TextureLoader.h"
#include <iostream>
#include <cstring>

unsigned int OpenEngine::Texture2D::mainUnit = GL_TEXTURE0;

template<typename T>
OpenEngine::Loader<T> * OpenEngine::Resource<T>::defaultLoader = new TextureLoader();

OpenEngine::Texture2D::Texture2D() : texUnit(mainUnit = ((mainUnit + 1) % 16))
{
    s_wrap = GL_REPEAT;
    t_wrap = GL_REPEAT;
    min_filter = GL_LINEAR_MIPMAP_LINEAR;
    mag_filter = GL_LINEAR;
}
OpenEngine::Texture2D::Texture2D(unsigned char *_data, unsigned int _w, unsigned int _h, unsigned int _stride) : Texture2D()
{
    load(_data, _w, _h, _stride);
}
OpenEngine::Texture2D::Texture2D(const OpenEngine::Texture2D &b)
{
    *this = b;
}
OpenEngine::Texture2D::Texture2D(OpenEngine::Texture2D &&b)
{
    if (data != nullptr)
    {
        delete[] data;
    }
    width = b.width;
    height = b.height;
    stride = b.stride;
    innerFormat = b.innerFormat;
    s_wrap = b.s_wrap;
    t_wrap = b.t_wrap;
    min_filter = b.min_filter;
    mag_filter = b.mag_filter;
    data = b.data;
    b.data = nullptr;
    generate();
    flush();
}
OpenEngine::Texture2D &OpenEngine::Texture2D::operator=(const Texture2D &b)
{
    if (data != nullptr)
    {
        delete[] data;
    }
    width = b.width;
    height = b.height;
    stride = b.stride;
    innerFormat = b.innerFormat;
    s_wrap = b.s_wrap;
    t_wrap = b.t_wrap;
    min_filter = b.min_filter;
    mag_filter = b.mag_filter;
    data = new unsigned char[width * height * stride];
    memcpy(data, b.data, width * height * stride * sizeof(unsigned char));
    generate();
    flush();
}
void OpenEngine::Texture2D::load(unsigned char *_data, unsigned int _w, unsigned int _h, unsigned int _stride)
{
    if (data != nullptr)
    {
        delete[] data;
    }
    data = _data;
    width = _w;
    height = _h;
    stride = _stride;
    deduceInnerFormat();
    generate();
    flush();
}

void OpenEngine::Texture2D::generate()
{
    glGenTextures(1, &textureID);
    bind();
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, s_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, t_wrap);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, mag_filter);
}
void OpenEngine::Texture2D::bind()
{
    glActiveTexture(GL_TEXTURE0 + texUnit);
    glBindTexture(GL_TEXTURE_2D, textureID);
}
void OpenEngine::Texture2D::flush()
{
    if (data == nullptr)
    {
        return;
    }
    bind();
    glTexImage2D(GL_TEXTURE_2D, 0, innerFormat, width, height, 0, innerFormat, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
}
bool OpenEngine::Texture2D::deduceInnerFormat()
{
    switch (stride)
    {
    case 1:
        innerFormat = GL_R8;
        break;
    case 3:
        innerFormat = GL_RGB;
        break;
    case 4:
        innerFormat = GL_RGBA;
        break;
    default:
        return false;
    }
    return true;
}

OpenEngine::Texture2D::~Texture2D()
{
    if (data != nullptr)
    {
        delete[] data;
    }
}