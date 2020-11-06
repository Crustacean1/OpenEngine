#include "Lib/Game/Game.h"
#include "Lib/Scene/Scene.h"

int main(int argc, char ** argv)
{
    OpenEngine::Game game;
    
    game.initGame();
    game.loadGame();
    game.gameLoop();
    
    return 0;
}