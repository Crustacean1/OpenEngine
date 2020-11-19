#ifndef MATERIAL
#define MATERIAL

#include "../Uniform/Uniform.h"
#include "../Texture/Texture.h"

namespace OpenEngine
{
    class Material : public Uniform<Material>
    {
    public:

        constexpr static char* basename = "materials";
        constexpr static unsigned int maxUniformsCount = 16;

        float shininess;
        Texture2D diff;
        Texture2D spec;
        Texture2D norm;

        Material() : diff(),spec(),norm(),shininess(32){}

        void update();
        void activate();
    };
}; // namespace OpenEngine

#endif /*MATERIAL*/