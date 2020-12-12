#ifndef SINGLETON
#define SINGLETON

namespace OpenEngine
{
    template<typename T>
    class Singleton
    {
        static T * instance;
        protected:
        Singleton(){}
        public:
        static T * getInstance()
        {
            if(instance==nullptr)
            {
                instance = new T;
            }
            return instance;
        }
    };
    template<typename T>
    T * Singleton<T>::instance = nullptr;
};

#endif /*SINGLETON*/