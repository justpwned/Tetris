#include <iostream>
#include "game.hpp"

using namespace core;

int wmain(int argc, char *argv[]) 
{
    Game game("Tetris", 300, 720, "novem.ttf", 24);
    game.MainLoop();
    game.Clean();
    
    return 0;
}