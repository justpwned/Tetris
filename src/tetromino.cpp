#include "tetromino.hpp"

using namespace core::gameplay;

static const u8 TETROMINO_1[] = {
    0, 0, 0, 0,
    1, 1, 1, 1,
    0, 0, 0, 0,
    0, 0, 0, 0
};

static const u8 TETROMINO_2[] = {
    2, 2,
    2, 2
};

static const u8 TETROMINO_3[] = {
    0, 0, 0,
    3, 3, 3,
    0, 3, 0
};

static const u8 TETROMINO_4[] = {
    0, 4, 4,
    4, 4, 0, 
    0, 0, 0
};

static const u8 TETROMINO_5[] = {
    5, 5, 0,
    0, 5, 5,
    0, 0, 0
};

static const u8 TETROMINO_6[] = {
    6, 0, 0,
    6, 6, 6,
    0, 0, 0
};

static const u8 TETROMINO_7[] = {
    0, 0, 7,
    7, 7, 7,
    0, 0, 0
};

const Tetromino Tetromino::s_tetrominos[Tetromino::s_numberOfTetrominos] = {
    Tetromino(TETROMINO_1, 4),
    Tetromino(TETROMINO_2, 2),
    Tetromino(TETROMINO_3, 3),
    Tetromino(TETROMINO_4, 3),
    Tetromino(TETROMINO_5, 3),
    Tetromino(TETROMINO_6, 3),
    Tetromino(TETROMINO_7, 3),
};

u8 Tetromino::GetValue(i32 t_row, i32 t_col, i32 t_rotation)
{
    switch (t_rotation % 4)
    {
        case 0:
        {
            return m_data[t_row * m_side + t_col];
        } break;
        
        case 1:
        {
            return m_data[(m_side - t_col - 1) * m_side + t_row];
        } break;
        
        case 2:
        {
            return m_data[(m_side - t_row - 1) * m_side + (m_side - t_col - 1)];
        } break;
        
        case 3:
        {
            return m_data[t_col * m_side + (m_side - t_row - 1)];
        } break;
    }
    
    return 0;
}