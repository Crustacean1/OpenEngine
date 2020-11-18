#ifndef POINTLIGHT
#define POINTLIGHT

#define MAX_LIGHT_COUNT 5

#include "Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OpenEngine
{
    class PointLight : public Light, public Uniform<PointLight>
    {
        constexpr static char * basename = "pLights";
        constexpr static unsigned int maxLightsCount = 5;
    public:
        glm::vec3 position;
        glm::vec3 color;

        void update();

    };
}; // namespace OpenEngine

#endif /*POINTLIGHT*/