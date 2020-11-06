#ifndef SCENE
#define SCENE

#include <map>
#include <set>
#include <string>
#include <memory>

namespace OpenEngine
{
    class Object;
    class Render;
    class Scene
    {
        std::map<std::string,std::shared_ptr<Object>> objects;
        std::set<std::shared_ptr<Render>> renders;
        //Render???
        public:

        void init();
        void add(std::shared_ptr<Object> _object);
        std::shared_ptr<Object> drop(std::shared_ptr<Object> _object);
        void add(std::shared_ptr<Render> _object);
        std::shared_ptr<Render> drop(std::shared_ptr<Render> _object);
        void render();
        void update();

    };
}; // namespace OpenEngine

#endif /*SCENE*/