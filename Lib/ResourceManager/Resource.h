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
        static const Loader<T> * defLoader;
    };
    template<typename T>
    const Loader<T> * Resource<T>::defLoader = T::defaultLoader;
};

#endif /*RESOURCE*/