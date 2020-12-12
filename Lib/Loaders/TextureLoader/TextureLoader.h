#ifndef TEXTURELOADER
#define TEXTURELOADER

#include "../Loader.h"

namespace OpenEngine
{
    class Texture2D;

    class TextureLoader : public Loader<Texture2D>
    {

        public:
        std::shared_ptr<Texture2D> load(std::string filename) const override;
    };
};

#endif /*TEXTURELOADER*/