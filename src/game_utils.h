#ifndef GAME_UTILS_H
#define GAME_UTILS_H

#include "common_utils.h"

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
        class Stats;
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

struct GameTime
{
    f32 nextDropTime;
    f32 highlightEndTime;
    f32 time;
};

struct GameState
{
    core::gameplay::Board *board;
    core::gameplay::Piece *piece;
    core::gameplay::Stats *stats;
    
    GamePhase phase;
    GameTime time;
};

struct InputState
{
    u8 left;
    u8 right;
    u8 up;
    u8 down;
    u8 space;
    u8 enter;
    u8 z;
    
    i8 dleft;
    i8 dright;
    i8 dup;
    i8 ddown;
    i8 dspace;
    i8 denter;
    i8 dz;
};

#endif