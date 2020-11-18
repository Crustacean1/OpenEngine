#ifndef DRIECTIONALLIGHT
#define DIRECTIONALLIGHT

#include "Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

namespace OpenEngine
{
    class DirectionalLight : public Light<DirectionalLight>
    {
    public:
        glm::vec3 direction;
        glm::vec3 color;
        void update();
    };
}; // namespace OpenEngine

#endif /*DIRECTIONALLIGHT*/