#ifndef RESOURCEMANAGER
#define RESOURCEMANAEGR

#include <string>

namespace OpenEngine
{
    template<typename T>
    class UID
    {
        static std::string incrament(std::string & ind);
        static constexpr char * mainID = "\1";
        std::string * ID;
        public:
        std::string * getID();
        UID();
    };
    class ResourceManager
    {
        ResourceManager();
        public:
        ResourceManager * getResourceManager();
        //UID * operator[](const std::string & index);
    };
};

#endif /*RESOURCEMANAGER*/