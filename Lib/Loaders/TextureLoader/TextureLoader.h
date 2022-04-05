#ifndef TEXTURELOADER
#define TEXTURELOADER

#include "../../Utilities/Singleton/Singleton.h"
#include "../Loader.h"

namespace OpenEngine
{
    class Texture2D;

    class TextureLoader : public Singleton<TextureLoader>, public Loader<Texture2D>
    {
        friend Singleton<TextureLoader>;
        protected:
        TextureLoader(){}
        public:
        std::shared_ptr<Texture2D> load(std::string filename);
    };
};

#endif /*TEXTURELOADER*/