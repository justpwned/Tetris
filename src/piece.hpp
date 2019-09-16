#ifndef PIECE_HPP
#define PIECE_HPP

#include "board.hpp"
#include "tetromino.hpp"
#include "game_utils.hpp"
#include "stats.hpp"

namespace core
{
    namespace gameplay
    {
        class Piece
        {
            private:
            
            Board *m_board;
            GameTime *m_time;
            Stats *m_stats;
            
            i32 m_tetrominoIndex;
            i32 m_rowOffset;
            i32 m_colOffset;
            i32 m_rotation;
            
            public:
            
            Piece() {}
            
            Piece(Board *t_board, GameTime *t_time, Stats *t_stats, i32 t_tetrominoIndex, i32 t_rowOffset, i32 t_colOffset, i32 t_rotation)
                : m_board(t_board), m_time(t_time), m_stats(t_stats), m_tetrominoIndex(t_tetrominoIndex), m_rowOffset(t_rowOffset), m_colOffset(t_colOffset), m_rotation(t_rotation) {}
            
            bool IsValid();
            void MergeWithBoard();
            void HardDrop();
            bool SoftDrop();
            void SpawnNewPiece();
            void DrawPiece(i32 t_xOffset, i32 t_yOffset, bool outline = false);
            
            inline i32 GetTetrominoIndex() const { return m_tetrominoIndex; }
            inline i32 GetRowOffset()      const { return m_rowOffset; }
            inline i32 GetColOffset()      const { return m_colOffset; }
            inline i32 GetRotation()       const { return m_rotation; }
            
            inline void SetTetrominoIndex(i32 t_tetrominoIndex) { m_tetrominoIndex = t_tetrominoIndex; }
            inline void SetRowOffset(i32 t_rowOffset) { m_rowOffset = t_rowOffset; }
            inline void SetColOffset(i32 t_colOffset) { m_colOffset = t_colOffset; }
            inline void SetRotation(i32 t_rotation)   { m_rotation = t_rotation; }
        };
    }
}

#endif