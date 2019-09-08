#include <iostream>
#include <time.h>

#include "game.hpp"

using namespace core;
using namespace core::graphics;

Game::Game(const char *t_title, i32 t_xPos, i32 t_yPos, i32 t_windowWidth, i32 t_windowHeight, const char *t_fontName, i32 t_fontSize)
{
    if (!SDL_Init(SDL_INIT_EVERYTHING))
    {
        std::cout << "SDL has been initialized successfully\n";
        
        m_window = SDL_CreateWindow(t_title, t_xPos, t_yPos, t_windowWidth,
                                    t_windowHeight, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
        
        if (m_window)
        {
            std::cout << "SDL window has been created successfully\n";
            
            m_renderer = SDL_CreateRenderer(m_window, -1, 
                                            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            
            if (m_renderer)
            {
                std::cout << "SDL renderer has been created successfully\n";
            }
            else
            {
                std::cerr << "Renderer could not be created. SDL error: " 
                    << SDL_GetError() << "\n";
                exit(1);
            }
        }
        else
        {
            std::cerr << "Window could not be created. SDL error: " << SDL_GetError() << "\n";
            exit(1);
        }
    }
    else
    {
        std::cerr << "Unable to intialize SDL. SDL error: " << SDL_GetError() << "\n";
        exit(1);
    }
    
    if (!TTF_Init())
    {
        std::cout << "SDL_TTF has been initialized successfully\n";
        
        m_font = TTF_OpenFont(t_fontName, t_fontSize);
        
        if (m_font)
        {
            std::cout << "Font " << t_fontName << "(" << t_fontSize 
                << ") has been loaded\n";
        }
        else
        {
            std::cerr << "Font " << t_fontName << "(" << t_fontSize 
                << ") has not been loaded\n";
            exit(1);
        }
    }
    
    else
    {
        std::cerr << "Unable to initialize SDL_TTF. SDL_TTF error: " << TTF_GetError() << "\n";
        exit(1);
    }
    
    m_gameWidth = t_windowWidth;
    m_gameHeight = t_windowHeight;
    m_running = true;
    
    m_graphics = Graphics(m_renderer);
    
    m_game = {};
    m_input = {};
    
    srand((u32)time(NULL));
}

void Game::HandleEvents()
{
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            Quit();
        }
    }
}

void Game::HandleInput()
{
    i32 keyCount;
    const u8 *keyStates = SDL_GetKeyboardState(&keyCount);
    
    if (keyStates)
    {
        if (keyStates[SDL_SCANCODE_ESCAPE])
        {
            Quit();
        }
        
        InputState prevInput = m_input;
        
        m_input.left   = keyStates[SDL_SCANCODE_LEFT];
        m_input.right  = keyStates[SDL_SCANCODE_RIGHT];
        m_input.up     = keyStates[SDL_SCANCODE_UP];
        m_input.down   = keyStates[SDL_SCANCODE_DOWN];
        m_input.a      = keyStates[SDL_SCANCODE_SPACE];
        
        m_input.dleft  = m_input.left - prevInput.left;
        m_input.dright = m_input.right - prevInput.right;
        m_input.dup    = m_input.up - prevInput.up;
        m_input.ddown  = m_input.down - prevInput.down;
        m_input.da     = m_input.a - prevInput.a;
    }
}

void Game::Update()
{
    
}

void Game::Render()
{
    SDL_SetRenderDrawColor(m_renderer, 100, 100, 100, 255);
    SDL_RenderClear(m_renderer);
    
    m_graphics.DrawText(m_font, "Hello there", 300, 100, TEXT_ALIGN_LEFT,
                        Color(255, 0, 0));
    
    m_graphics.DrawText(m_font, "Hello there", 300, 100, TEXT_ALIGN_CENTER,
                        Color(0, 255, 0));
    
    m_graphics.DrawText(m_font, "Hello there", 300, 100, TEXT_ALIGN_RIGHT,
                        Color(0, 0, 255));
}

void Game::MainLoop()
{
    while (Running())
    {
        HandleEvents();
        HandleInput();
        
        Update();
        Render();
        
        SDL_RenderPresent(m_renderer);
    }
}

void Game::Clean()
{
    std::cout << "Closing the game. Cleaning up all the mess...\n";
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    TTF_CloseFont(m_font);
    TTF_Quit();
    SDL_Quit();
}