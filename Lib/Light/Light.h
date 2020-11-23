#ifndef LIGHT
#define LIGHT

#include "../Component/Component.h"
#include "../Uniform/Uniform.h"
#include <string>
#include <glm/glm.hpp>
namespace OpenEngine
{
    class Shader;

    class Light : public Component<Light>
    {
    protected:
        Light(Object & _obj) : Component(_obj){}

        bool active = true;
    public:

        virtual void illuminate(const glm::mat4 &mat) = 0;
    };
    
}; // namespace OpenEngine

#endif /*LIGHT*/