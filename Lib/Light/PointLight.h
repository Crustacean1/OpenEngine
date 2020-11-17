#ifndef LIGHT
#define LIGHT

#include "../Uniform/Uniform.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace OpenEngine
{
    class PointLight : public Uniform
    {
        glm::vec3 position;
        glm::vec3 color;

        public:
        void update();
    };
};

#endif /*LIGHT*/