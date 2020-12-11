#ifndef LOADER
#define LOADER

#include <string>
#include <memory>

namespace OpenEngine
{
    template<typename T>
    class Loader
    {
        public:
        virtual std::shared_ptr<T> load(std::string filename) = 0;
    };
};


#endif /*LOADER*/