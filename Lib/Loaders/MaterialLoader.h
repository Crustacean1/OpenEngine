#ifndef MATERIALLOADER
#define MATERIALLOADER

#include <map>
#include <string>

namespace OpenEngine
{
    class Material;
    class MaterialLoader
    {
        public:
        std::map<std::string,Material *> loadMaterial(const char * filename);
    };
};

#endif /*MATERIALLOADER*/