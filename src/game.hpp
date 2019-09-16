#ifndef GAME_HPP
#define GAME_HPP

#include "SDL.h"
#include "SDL_ttf.h"
#include "graphics\graphics.hpp"
#include "board.hpp"
#include "piece.hpp"
#include "stats.hpp"
#include "game_utils.hpp"

namespace core
{
    class Game
    {
        private:
        
        i32 m_gameWidth;
        i32 m_gameHeight;
        
        SDL_Window *m_window;
        SDL_Renderer *m_renderer;
        
        GameState m_game;
        InputState m_input;
        
        TTF_Font *m_font;
        
        bool m_running;
        
        // Update methods
        void UpdateGameStart();
        void UpdateGamePlay();
        void UpdateGameLine();
        void UpdateGameOver();
        
        // Rendering methods
        void RenderGameStart(i32 t_xOffset, i32 t_yOffset);
        void RenderGamePlay(i32 t_xOffset, i32 t_yOffset);
        void RenderGameLine(i32 t_xOffset, i32 t_yOffset);
        void RenderGameOver(i32 t_xOffset, i32 t_yOffset);
        void RenderGameStats(i32 t_xOffset, i32 t_yOffset);
        
        public:
        
        Game(const char *t_title, i32 t_xPos, i32 t_yPos, i32 t_windowWidth, i32 t_windowHeight, const char *t_fontName);
        
        Game(const char *t_title, i32 t_windowWidth, i32 t_windowHeight, const char *t_fontName) 
            : Game(t_title, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
                   t_windowWidth, t_windowHeight, t_fontName) {}
        
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
    };
}

#endif