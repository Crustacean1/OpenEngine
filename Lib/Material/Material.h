#ifndef MATERIAL
#define MATERIAL

#include "../Uniform/Uniform.h"
#include "../Texture/Texture.h"

namespace OpenEngine
{
    class Material : public Uniform
    {
        std::string shaderId;
        unsigned int ID;
    public:
        float shininess;
        Texture2D diff;
        Texture2D spec;
        Texture2D norm;

        Material() : diff(),spec(),norm(),ID(0),shininess(32){}

        void setId(unsigned int _id);
        unsigned int getId(){return ID;}

        void update();
    };
}; // namespace OpenEngine

#endif /*MATERIAL*/