#ifndef MATERIAL
#define MATERIAL

#include "../Uniform/Uniform.h"
#include "../Texture/Texture.h"

namespace OpenEngine
{
    class Material : public Uniform<Material>
    {
        friend Uniform<Material>;
        constexpr static char* baseline = "materials";
        constexpr static unsigned int maxUniformsCount = 5;
    public:
        float shininess;
        Texture2D diff;
        Texture2D spec;
        Texture2D norm;

        Material() : Uniform(),diff(),spec(),norm(),shininess(32){}

        void update();
    };
}; // namespace OpenEngine

#endif /*MATERIAL*/