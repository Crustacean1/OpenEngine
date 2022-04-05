#ifndef CUBEMAP
#define CUBEMAP

#include <string>

namespace OpenEngine
{
    class Cubemap
    {
        static unsigned int mainUnit;
        int texUnit;
        unsigned int textureID;
        //unsigned char * data[6] = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr};
        static const char * faces[6];

        public:
        Cubemap();
        Cubemap(const std::string & filename,const std::string &ext);
        Cubemap(unsigned char r,unsigned char g,unsigned char b);
        void generate();
        unsigned int getTexID(){return textureID;}
        int getUnitID(){return texUnit;}
        void bind();
        void flush(unsigned char * data,int i);

        bool loadFromFile(const std::string & filename,const std::string & extension);
        void createFromColor(unsigned char r,unsigned char g,unsigned char b);
    };
};

#endif /*CUBEMAP*/