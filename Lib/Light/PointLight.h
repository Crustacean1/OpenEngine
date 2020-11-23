#ifndef POINTLIGHT
#define POINTLIGHT

#include "Light.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OpenEngine
{
    class PointLight : public Light, public Uniform<PointLight>
    {
        constexpr static char *basename = "pLights";
        constexpr static unsigned int maxUniformsCount = 16;
        friend Uniform<PointLight>;
        glm::vec3 lastViewPosition;

    public:
        PointLight(Object &_obj, glm::vec3 _c = glm::vec3(1,1,1), float _amb = 0.05f, float _diff = 0.5f, float _spec = 0.25f)
            : Light(_obj), color(_c),ambient(_amb),diffuse(_diff),specular(_spec) {}
        glm::vec3 color;
        float ambient;
        float diffuse;
        float specular;

        void update();
        void illuminate(const glm::mat4 & mat);
    };
}; // namespace OpenEngine

#endif /*POINTLIGHT*/