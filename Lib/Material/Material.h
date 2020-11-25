#ifndef MATERIAL
#define MATERIAL

#include "../Uniform/Uniform.h"
#include "../Texture/Texture.h"

namespace OpenEngine
{
    class Material
    {
        public:
        virtual void activate();
    };
    class Material2D
    {

    };
    class Material3D : public Uniform<Material3D>
    {
    public:

        constexpr static char* basename = "materials";
        constexpr static unsigned int maxUniformsCount = 16;

        float shininess;

        Texture2D amb;
        Texture2D diff;
        Texture2D spec;
        Texture2D norm;

        Material3D();
        void update();
        void activate();
    };
}; // namespace OpenEngine

#endif /*MATERIAL*/