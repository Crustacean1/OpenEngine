#ifndef TEXTURE
#define TEXTURE

#include <string>

namespace OpenEngine
{
    class Texture2D
    {
        static unsigned int mainUnit;
        int texUnit;
        unsigned char * data;

        unsigned int textureID;

        int width,height;
        int stride;
        unsigned int innerFormat;

        public:

        Texture2D();
        Texture2D(const std::string & filename);
        Texture2D(unsigned char r,unsigned char g,unsigned char b);//Single color one pixel texture

        void loadFromFile(const std::string & filename);
        void generate();

        static unsigned int getMaxTextureCount();
        unsigned int getTexID(){return textureID;}
        int getUnitID(){return texUnit;}

        unsigned int getHeight(){return height;}
        unsigned int getWidth(){return width;}

        void flush();
        void bind();
    };
};

#endif /*TEXTURE*/