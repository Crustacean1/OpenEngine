#ifndef MANAGERTYPES
#define MANAGERTYPES

//these types are mutually exclusive, serve only as an interface for scene to use

namespace OpenEngine
{
    class Temporal
    {
    public:
        virtual void update(double delta) = 0;
    };
    class Invariant
    {
    public:
        virtual void execute() = 0;
    };
    class Passive
    {
    };
}; // namespace OpenEngine

#endif /*MANAGERTYPES*/