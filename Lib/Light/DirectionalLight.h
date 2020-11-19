#ifndef DRIECTIONALLIGHT
#define DIRECTIONALLIGHT

#include "Light.h"
#include <glm/glm.hpp>
#include <string>

namespace OpenEngine
{
    class DirectionalLight : public Light, public Uniform<DirectionalLight>
    {
    public:
        glm::vec3 color;
        void update();
    };
}; // namespace OpenEngine

#endif /*DIRECTIONALLIGHT*/