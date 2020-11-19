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
        Light(Object & _obj,unsigned int _amb,unsigned int _diff,unsigned int _spec) : 
        Component(_obj),ambient(_amb),diffuse(_diff),specular(_spec){}

        bool active = true;
    public:

        float ambient;
        float diffuse;
        float specular;

        virtual void illuminate(const glm::mat4 &mat) = 0;
    };
    
}; // namespace OpenEngine

#endif /*LIGHT*/