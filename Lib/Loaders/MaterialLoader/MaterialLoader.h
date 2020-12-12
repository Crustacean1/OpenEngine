#ifndef MATERIALLOADER
#define MATERIALLOADER

#include <map>
#include <string>

namespace OpenEngine
{
    class Material3D;
    class MaterialLoader
    {
        public:
        std::map<std::string,Material3D *> load(std::string filename);
    };
};

#endif /*MATERIALLOADER*/