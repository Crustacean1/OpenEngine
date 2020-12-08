#ifndef DRIECTIONALLIGHT
#define DIRECTIONALLIGHT

#include "Light.h"
#include "Helios.h"
#include <glm/glm.hpp>
#include <string>

namespace OpenEngine
{
    class DirectionalLight : public Light, public Uniform<DirectionalLight>
    {
        constexpr static char * basename = "dLights";
        constexpr static unsigned int maxUniformsCount = 16;
        friend Uniform<DirectionalLight>;
        glm::vec3 lastViewDirection;
    public:
        DirectionalLight(Object & _obj, glm::vec3 _c,float _amb = 0.05f,float _diff = 0.5f,float _spec = 0.25f)
        : Light(_obj,this), color(_c),ambient(_amb),diffuse(_diff),specular(_spec){}
        glm::vec3 color;
        float ambient;
        float diffuse;
        float specular;
        void update();
        void illuminate(const glm::mat4 & mat);
        BaseComponent* instantiate() override{return new DirectionalLight(*this);}
    };
}; // namespace OpenEngine

#endif /*DIRECTIONALLIGHT*/