#ifndef SCENE
#define SCENE

#include "Object.h"


namespace OpenEngine
{
    class Scene
    {
        std::map<std::string,std::shared_ptr<Object>> objects;
        
        public:

    };
}; // namespace OpenEngine

#endif /*SCENE*/