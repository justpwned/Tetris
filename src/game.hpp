#ifndef GAME_HPP
#define GAME_HPP

#include "SDL.h"
#include "SDL_ttf.h"
#include "graphics\graphics.hpp"
#include "utils.h"
#include "board.hpp"
#include "piece.hpp"

static const i32 BOARD_COLS = 10; // WIDTH
static const i32 BOARD_ROWS = 22; // HEIGHT
static const i32 BOARD_VISIBLE_ROWS = 20; // VISIBLE HEIGHT
static const i32 BOARD_GRID_SIZE = 30;

namespace core
{
    enum GamePhase
    {
        GAME_PHASE_START,
        GAME_PHASE_PLAY,
        GAME_PHASE_LINE,
        GAME_PHASE_OVER,
        GAME_PHASE_TOTAL
    };
    
    struct GameState
    {
        gameplay::Board board;
        i32 lines[BOARD_ROWS]; // Move lines to board class later
        
        gameplay::Piece piece;
        
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
        u8 space;
        u8 enter;
        
        i8 dleft;
        i8 dright;
        i8 dup;
        i8 ddown;
        i8 dspace;
        i8 denter;
    };
    
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
    };
}

#endif