#ifndef GAME_H
#define GAME_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "graphics\graphics.hpp"
#include "utils.h"

namespace core
{
    enum GamePhase
    {
        GAME_PHASE_START,
        GAME_PHASE_PLAY,
        GAME_PHASE_LINE,
        GAME_PHASE_OVER
    };
    
    struct GameState
    {
        GamePhase phase;
        
        i32 startLevel;
        i32 level;
        i32 lineCount;
        i32 points;
        
        i32 nextDropTime;
        i32 highlightEndTime;
        i32 time;
    };
    
    struct InputState
    {
        u8 left;
        u8 right;
        u8 up;
        u8 down;
        u8 a;
        
        i8 dleft;
        i8 dright;
        i8 dup;
        i8 ddown;
        i8 da;
    };
    
    class Game
    {
        private:
        
        i32 m_gameWidth;
        i32 m_gameHeight;
        
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        
        graphics::Graphics m_graphics;
        GameState m_game;
        InputState m_input;
        TTF_Font *m_font;
        
        bool m_running;
        
        public:
        
        Game(const char *t_title, i32 t_xPos, i32 t_yPos, i32 t_windowWidth, i32 t_windowHeight, const char *t_fontName, i32 t_fontSize);
        
        Game(const char *t_title, i32 t_windowWidth, i32 t_windowHeight, const char *t_fontName, i32 t_fontSize) 
            : Game(t_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                   t_windowWidth, t_windowHeight, t_fontName, t_fontSize) {}
        
        void HandleEvents();
        void HandleInput();
        void Update();
        void Render();
        void MainLoop();
        void Clean();
        
        inline void Quit() { m_running = false; }
        
        inline bool Running()              const { return m_running; }
        inline i32 getGameWidth()          const { return m_gameWidth; }
        inline i32 getGameHeight()         const { return m_gameHeight; }
        inline SDL_Renderer* getRenderer() const { return m_renderer; }
    };
}

#endif