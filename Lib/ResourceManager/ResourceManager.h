#ifndef RESOURCEMANAGER
#define RESOURCEMANAEGR

#include <string>

namespace OpenEngine
{
    class ResourceManager
    {
        ResourceManager();
        public:
        ResourceManager * getResourceManager();
        //UID * operator[](const std::string & index);
    };
};

#endif /*RESOURCEMANAGER*/