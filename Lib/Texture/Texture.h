#ifndef TEXTURE
#define TEXTURE

#include <string>

namespace OpenEngine
{
    class Texture2D
    {
        static unsigned int mainID;
        char * ptr;

        unsigned int width,height;

        public:

        Texture2D();
        Texture2D(const std::string & filename);
        Texture2D(int r,int g,int b);//Single color one pixel texture

        void loadFromFile(std::string & filename);

        static unsigned int getMaxTextureCount();
        unsigned int getTexID();

        unsigned int getHeight();
        unsigned int getWidth();

        void flush();

    };
};

#endif /*TEXTURE*/