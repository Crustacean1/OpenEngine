#ifndef MATERIAL
#define MATERIAL

#include "../Uniform/Uniform.h"
#include "../Texture/Texture.h"
#include "Cubemap.h"

namespace OpenEngine
{
    class Material
    {
    public:
        virtual void activate() = 0;
        virtual Shader *getShader() = 0;
    };
    class Material2D
    {
    };
    class Material3D : public Uniform<Material3D>, public Material
    {
    public:
        constexpr static char *basename = "materials";
        constexpr static unsigned int maxUniformsCount = 16;

        float shininess;

        std::shared_ptr<Texture2D> amb;
        std::shared_ptr<Texture2D> diff;
        std::shared_ptr<Texture2D> spec;
        std::shared_ptr<Texture2D> norm;

        Material3D();
        void update();
        void activate() override;
        Shader *getShader() { return shader; }
    };
    class CubeMaterial : public Material, public Uniform<CubeMaterial>
    {

    public:
        constexpr static char *basename = "cubemap";
        constexpr static unsigned int maxUniformsCount = 1;
        Cubemap cubemap;
        void update() override;
        void activate() override;
        CubeMaterial();
        Shader *getShader() { return shader; }
    };
    class EmptyMaterial : public Material, public Uniform<EmptyMaterial>
    {
    public:
        constexpr static char *basename = "emptymaterial";
        constexpr static unsigned int maxUniformsCount = 1;
        void activate() override {}
        void update() override {}
        Shader *getShader() { return shader; }
    };
}; // namespace OpenEngine

#endif /*MATERIAL*/