#ifndef BASECOMPONENT
#define BASECOMPONENT

namespace OpenEngine
{
    class Object;
    class Scene;

    class BaseComponent
    {

    protected:
        BaseComponent(Object &_parent);
        Object &object;

    public:
        void setObject(Object &_obj);

        virtual void onStart() {}
        virtual void onDestroy() {}

        virtual void onAttach() {}
        virtual void onDetach() {}

        virtual ~BaseComponent() {}
    };

}; // namespace OpenEngine

#endif /*BASECOMPONENT*/