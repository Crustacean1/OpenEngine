#ifndef TEXTURE
#define TEXTURE

#include <string>
#include <memory>
#include "../ResourceManager/Resource.h"

namespace OpenEngine
{
    class Texture2D : public Resource<Texture2D>
    {
        static unsigned int mainUnit;
        int texUnit;
        unsigned char * data = nullptr;

        unsigned int textureID;

        int width, height;
        int stride;
        int innerFormat;

        bool deduceInnerFormat();

        void setParams();

    public:
        Texture2D(unsigned char *_data, unsigned int _w, unsigned int _h, unsigned int _stride);
        Texture2D(const Texture2D &b);
        Texture2D(Texture2D &&b);
        Texture2D();
        Texture2D & operator=(const Texture2D &b);

        ~Texture2D();

        void create(unsigned int x,unsigned int y,unsigned int _stride);
        void createFromColor(unsigned char r,unsigned char g,unsigned char b);

        unsigned int getTexID() { return textureID; }
        int getUnitID() { return texUnit; }

        unsigned int getHeight() { return height; }
        unsigned int getWidth() { return width; }

        void flush();
        void bind();

        unsigned char *getData() { return data;}
        void load(unsigned char * _data,unsigned int _w,unsigned int _h,unsigned int _stride);

        int s_wrap;
        int t_wrap;
        int min_filter;
        int mag_filter;

        static const Loader<Texture2D> * defaultLoader; //default resource loader
    };
}; // namespace OpenEngine

#endif /*TEXTURE*/