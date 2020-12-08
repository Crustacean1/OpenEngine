#ifndef GAME
#define GAME

#include "../Object/Object.h"
#include "../Scene/Scene.h"
#include "../Window/Window.h"

namespace OpenEngine
{
    class Game
    {
        std::map<unsigned int, Scene *> scenes;
        Scene *currentScene = nullptr;
        Window &window;

    public:
        Game();
        void initGame();
        void loadGame(); //For testing , will be replaced
        void gameLoop();

        void addScene(Scene *_scene);
        void switchScene(unsigned int _scene);
    };
}; // namespace OpenEngine

#endif /*GAME*/