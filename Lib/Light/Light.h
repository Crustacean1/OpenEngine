#ifndef LIGHT
#define LIGHT

#include "../Component/Component.h"
#include "../Uniform/Uniform.h"
#include <string>

namespace OpenEngine
{
    class Shader;

    class Light : public Component<Light>
    {
    protected:
        Light(Object & _obj) : Component(_obj){}

    public:
        bool active = true;

        float ambient;
        float diffuse;
        float specular;

        void illuminate();
    };
    
}; // namespace OpenEngine

#endif /*LIGHT*/