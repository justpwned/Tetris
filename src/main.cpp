#include <iostream>
#include "game.hpp"

#include <fstream>
#include <cstring>

using namespace core;

int main(int argc, char *argv[]) 
{
    Game game("Tetris", 300, 720, "novem.ttf");
    game.MainLoop();
    game.Clean();
    
    return 0;
}