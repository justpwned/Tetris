#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "utils.h"

#define BOARD_COLS 10         // WIDTH
#define BOARD_ROWS 22         // HEIGHT
#define BOARD_VISIBLE_ROWS 20 // VISIBLE HEIGHT
#define BOARD_GRID_SIZE 30

namespace core
{
    namespace gameplay
    {
        class Board;
        class Piece;
    }
}

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
    core::gameplay::Board *board;
    i32 lines[BOARD_ROWS]; // Move lines to board class later
    
    core::gameplay::Piece *piece;
    
    GamePhase phase;
    
    i32 startLevel;
    i32 level;
    i32 lineCount;
    i32 points;
    
    f32 nextDropTime;
    f32 highlightEndTime;
    f32 time;
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

#endif