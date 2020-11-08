#ifndef BEHAVIOUR
#define BEHAVIOUR

namespace OpenEngine
{
    class Behaviour
    {
    public:
        virtual void init() = 0;
        virtual void update(double delta) = 0;
    };
}; // namespace OpenEngine

#endif /*BEHAVIOUR*/