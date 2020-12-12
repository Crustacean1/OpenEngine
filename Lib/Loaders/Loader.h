#ifndef LOADER
#define LOADER

#include <string>
#include <memory>

namespace OpenEngine
{
    std::string getFullResourcePath(std::string filename);
    template<typename T>
    class Loader
    {
        public:
        virtual std::shared_ptr<T> load(std::string filename) const = 0;
    };
};


#endif /*LOADER*/