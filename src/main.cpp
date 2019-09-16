#include <iostream>
#include "game.hpp"

#include <fstream>
#include <cstring>

using namespace core;

int wmain(int argc, char *argv[]) 
{
    Game game("Tetris", 300, 720, "novem.ttf");
    game.MainLoop();
    game.Clean();
    
    return 0;
}