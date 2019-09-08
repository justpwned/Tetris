#ifndef BOARD_H
#define BOARD_H

#include "utils.h"
#include "math\matrix.hpp"

namespace core
{
    namespace gameplay
    {
        class Board
        {
            private:
            
            i32 m_boardRows;
            i32 m_boardCols;
            i32 m_boardVisibleRows;
            i32 m_boardGridSize;
            
            math::mat m_boardData;
            
            public:
            
            // boardCols = boardWidth
            // boardRows = boardHeight
            
            Board() {}
            
            void Init(i32 t_boardRows, i32 t_boardCols, i32 t_boardVisibleRows, i32 t_boardGridSize)
            {
                m_boardRows = t_boardRows;
                m_boardCols = t_boardCols;
                m_boardVisibleRows = t_boardVisibleRows;
                m_boardGridSize = t_boardGridSize;
                m_boardData.Resize(t_boardRows, t_boardCols);
            }
            
            inline void Clear() { m_boardData.Clear(); }
            
            inline i32 getBoardCols()        const { return m_boardCols; }
            inline i32 getBoardRows()        const { return m_boardRows; }
            inline i32 getBoardVisibleRows() const { return m_boardVisibleRows; }
            inline i32 getBoardGridSize()    const { return m_boardGridSize; }
        };
    }
}

#endif