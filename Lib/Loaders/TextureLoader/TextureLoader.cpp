#define STB_IMAGE_IMPLEMENTATION
#include "../../Ext/stb_image.h"
#include <glad/glad.h>
#include "TextureLoader.h"
#include "../../Texture/Texture.h"
#include "../../Exception/Exception.h"

std::shared_ptr<OpenEngine::Texture2D> OpenEngine::TextureLoader::load(std::string filename) const
{
    int w, h, s;
    unsigned char *data = stbi_load(filename.c_str(), &w, &h, &s, 0);
    std::shared_ptr<Texture2D> tex(new Texture2D(data, w, h, s));

    return tex;
}