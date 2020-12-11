#ifndef RESOURCE
#define RESOURCE

namespace OpenEngine
{
    template<typename T>
    class Loader;

    template<typename T>
    class Resource
    {
        public:
        static const Loader<T> * defaultLoader;
    };
};

#endif /*RESOURCE*/