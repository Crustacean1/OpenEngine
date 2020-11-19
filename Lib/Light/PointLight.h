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
        constexpr static unsigned int maxUniformsCount = 5;
        friend Uniform<PointLight>;
        glm::vec3 lastViewPosition;

    public:
        PointLight(Object &_obj, glm::vec3 _c = glm::vec3(1,1,1), float _amb = 0.05f, float _diff = 0.25f, float _spec = 0.f)
            : Light(_obj,_amb,_diff,_spec), color(_c) {}
        glm::vec3 color;

        void update();
        void illuminate(const glm::mat4 & mat);
    };
}; // namespace OpenEngine

#endif /*POINTLIGHT*/