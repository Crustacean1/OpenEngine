#ifndef SCENE
#define SCENE

#include "../Object/Object.h"
#include "../Render/Render.h"


namespace OpenEngine
{
    class Scene
    {
        std::map<std::string,std::shared_ptr<Object>> objects;
        //Render???
        public:

        void render();
        void update();

    };
}; // namespace OpenEngine

#endif /*SCENE*/