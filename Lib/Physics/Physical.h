#ifndef PHYSICAL
#define PHYSICAL

#include "../Component/Component.h"
#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

namespace OpenEngine
{
    class Object;
    class PhysicManager;

    class Physical : Component<Physical, PhysicManager>
    {
        glm::vec3 angularMomentum;
        glm::vec3 powerMomentum;
        glm::vec3 velocity;
        glm::vec3 acceleration;

        double angDamp = 0.5;
        double velDamp = 0.5;

        double mass;

    public:
        Physical(Object &_obj,double _ad=0.5,double _vd = 0.5);
        void update(double delta);

        glm::vec3 getDisplacement(double delta);
        glm::vec3 getRotation(double delta);

        glm::vec3 getVelocity();
        glm::vec3 getAcceleration() { return glm::vec3(acceleration.x, acceleration.y, acceleration.z); }

        glm::vec3 getAngularMomentum() { return angularMomentum; }
        glm::vec3 getMomentOfPower() { return powerMomentum; }

        double getMass() { return mass; }
        void setMass(double _w) { mass = _w; }

        void actForce(glm::vec3 force) { acceleration += glm::vec3(force.x, force.y, force.z); }
        void actMomentum(glm::vec3 mop) { powerMomentum += glm::vec3(mop.x, mop.y, mop.z); }

        void setVelocityDampening(double _d){velDamp = _d;}
        void setAngularDampening(double _d){angDamp = _d;}

        BaseComponent* instantiate() override{return new Physical(*this);}
    };
}; // namespace OpenEngine

#endif /*PHYSICAL*/