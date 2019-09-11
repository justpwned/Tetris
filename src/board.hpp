#ifndef BOARD_HPP
#define BOARD_HPP

#include "SDL.h"
#include "common_utils.h"
#include "math\matrix.hpp"
#include "tetromino.hpp"
#include "game_utils.h"
#include "stats.hpp"

namespace core
{
    namespace gameplay
    {
        class Board
        {
            private:
            
            SDL_Renderer *m_renderer;
            
            i32 m_boardRows;
            i32 m_boardCols;
            i32 m_boardVisibleRows;
            i32 m_boardGridSize;
            
            math::mat m_boardData;
            
            public:
            
            // boardCols = boardWidth
            // boardRows = boardHeight
            
            Board(i32 t_boardRows, i32 t_boardCols, i32 t_boardVisibleRows, i32 t_boardGridSize);
            
            void DrawCell(i32 t_row, i32 t_col, i32 t_value, i32 t_xOffset, i32 t_yOffset, bool t_outline = false);
            
            void DrawPiece(i32 t_xOffset, i32 t_yOffset, bool t_outline = false);
            
            void DrawBoard(i32 t_xOffset, i32 t_yOffset);
            
            bool IsRowFilled(i32 t_row);
            bool IsRowEmpty(i32 t_row);
            
            void FindLines(Stats *t_stats);
            void ClearLines(Stats *t_stats);
            
            inline void Clear() { m_boardData.Clear(); }
            
            inline void SetCellValue(i32 t_row, i32 t_col, i32 t_value) 
            { m_boardData.SetValue(t_row, t_col, t_value); }
            
            inline i32 GetCellValue(i32 t_row, i32 t_col) const 
            { return m_boardData.GetValue(t_row, t_col); }
            
            inline i32 GetBoardCols()        const { return m_boardCols; }
            inline i32 GetBoardRows()        const { return m_boardRows; }
            inline i32 GetBoardVisibleRows() const { return m_boardVisibleRows; }
            inline i32 GetBoardGridSize()    const { return m_boardGridSize; }
        };
    }
}

#endif