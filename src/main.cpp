#include <iostream>
#include "Game.hpp"

int wmain(int argc, char **argv) 
{
    if (Game::Instance()->Init("Tetris", 300, 720, "novem.ttf", 24))
    {
        std::cout << "Game has been initialized successfully\n";
        
        Game::Instance()->MainLoop();
        Game::Instance()->Clean();
    }
    else
    {
        std::cerr << "Game failed to intialize. Closing...\n";
        return 1;
    }
    
    return 0;
}