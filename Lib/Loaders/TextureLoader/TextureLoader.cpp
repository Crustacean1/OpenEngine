#define STB_IMAGE_IMPLEMENTATION
#include "../../Ext/stb_image.h"
#include <glad/glad.h>
#include "TextureLoader.h"
#include "../../Texture/Texture.h"
#include "../../Exception/Exception.h"

std::shared_ptr<OpenEngine::Texture2D> OpenEngine::TextureLoader::load(std::string filename)
{
    int w, h, s;
    unsigned char *data = stbi_load(filename.c_str(), &w, &h, &s, 0);
    std::shared_ptr<Texture2D> tex(new Texture2D(data, w, h, s));

    return tex;
}
std::shared_ptr<OpenEngine::Texture2D> OpenEngine::TextureLoader::create(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
    unsigned char data[] = {r, g, b, a};
    unsigned int width, height, stride;
    width = height = 1;
    stride = 4;
    std::shared_ptr<Texture2D> tex(new Texture2D(data, width, height, stride));
    return tex;
}
std::shared_ptr<OpenEngine::Texture2D> OpenEngine::TextureLoader::create(unsigned int x, unsigned int y, unsigned char format)
{
    if (format > 4)
    {
        return nullptr;
    }
    int width = x;
    int height = y;
    unsigned char *data = new unsigned char[format * x * y];

    return std::shared_ptr<Texture2D>(new Texture2D(data, width, height, format));
}