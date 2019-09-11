#ifndef TETROMINO_HPP
#define TETROMINO_HPP

#include "common_utils.h"

namespace core
{
    namespace gameplay
    {
        class Tetromino
        {
            private:
            
            const u8 *m_data;
            i32 m_side;
            
            public:
            
            static const i32 s_numberOfTetrominos = 7;static const Tetromino s_tetrominos[Tetromino::s_numberOfTetrominos];
            
            Tetromino() {}
            
            Tetromino(const u8 *t_data, i32 t_side)
                : m_data(t_data), m_side(t_side) {}
            
            u8 GetValue(i32 t_row, i32 t_col, i32 t_rotation);
            
            inline i32 GetSide() const { return m_side; }
        };
    }
}

#endif