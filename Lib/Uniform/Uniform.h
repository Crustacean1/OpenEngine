#ifndef UNIFORM
#define UNIFORM

#include <string>

namespace OpenEngine
{
    class Shader;

    template <typename T>
    class Uniform
    {
        static std::string __basename;
        constexpr static unsigned int __maxUniformsCount = T::maxUniformsCount;
        static T *__uniforms[];
        static unsigned int __uniformsCount;

        static std::string createBasename(int a);
        static std::string toStr(int a); // helper function

        unsigned int uniformId;
        std::string uniformName;

    public:
        Shader *shader;

        //Uniform() : uniformId((__uniformsCount < __maxUniformsCount) * (__uniformsCount++) - (__uniformsCount > __maxUniformsCount)) { uniformName = createBasename(__uniformsCount); }
        Uniform(Shader *_sh = nullptr) : shader(_sh), uniformId((__uniformsCount < __maxUniformsCount) * (__uniformsCount++) - (__uniformsCount > __maxUniformsCount)) { uniformName = createBasename(uniformId); }

        virtual void update() = 0;

        ~Uniform()
        {
            if (uniformId > -1)
            {
                __uniforms[uniformId] = nullptr;
            }
            __uniformsCount--;
        }
        void unbind()
        {
            if (uniformId < 0)
            {
                return;
            }
            __uniforms[uniformId] = nullptr;
        }
        void bindTo(unsigned int _id)
        {
            __uniforms[_id]->unbind();
            __uniforms[_id] = this;
        }
        unsigned int getBinding() { return uniformId; }

        std::string getName() { return uniformName; }
    };

    template <typename T>
    std::string Uniform<T>::toStr(int a)
    {
        std::string res;
        do
        {
            res = (char)(a % 10 + '0') + res;
            a /= 10;
        } while (a > 0);
        return res;
    }
    template <typename T>
    std::string Uniform<T>::createBasename(int a)
    {
        if (__maxUniformsCount == 1)
        {
            return __basename;
        }
        return __basename + "[" + toStr(a) + "]";
    }

    template <typename T>
    std::string OpenEngine::Uniform<T>::__basename = T::basename;

    //template <typename T>
    //unsigned int OpenEngine::Uniform<T>::__maxUniformsCount = T::maxUniformsCount;

    template <typename T>
    T *OpenEngine::Uniform<T>::__uniforms[OpenEngine::Uniform<T>::__maxUniformsCount];

    template <typename T>
    unsigned int OpenEngine::Uniform<T>::__uniformsCount = 0;
}; // namespace OpenEngine

#endif /*UNIFORM*/