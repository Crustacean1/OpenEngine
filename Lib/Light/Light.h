#ifndef LIGHT
#define LIGHT

#include "../Component/Component.h"
#include "../Uniform/Uniform.h"
#include <string>
#include <glm/glm.hpp>
namespace OpenEngine
{
    class Shader;
    class Helios;

    class Light : public Component<Light,Helios>
    {
    protected:
        template<typename T>
        Light(Object & _obj,T*_ptr):Component(_obj,_ptr){}

        bool active = true;
    public:

        virtual void illuminate(const glm::mat4 &mat) = 0;
    };
    
}; // namespace OpenEngine

#endif /*LIGHT*/