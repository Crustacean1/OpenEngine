#ifndef TEXTURELOADER
#define TEXTURELOADER

#include "../Loader.h"

namespace OpenEngine
{
    class Texture2D;

    class TextureLoader : public Loader<Texture2D>
    {

        public:
        std::shared_ptr<Texture2D> load(std::string filename) override;
        std::shared_ptr<Texture2D> create(unsigned char r,unsigned char g,unsigned char b,unsigned char a);
        std::shared_ptr<Texture2D> create(unsigned int x,unsigned int y,unsigned char format);
    };
};

#endif /*TEXTURELOADER*/