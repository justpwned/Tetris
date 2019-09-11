#include "piece.hpp"

using namespace core::gameplay;

bool Piece::IsValid()
{
    Tetromino tetromino = Tetromino::s_tetrominos[m_tetrominoIndex];
    
    for (i32 row = 0; row < tetromino.GetSide(); ++row)
    {
        for (i32 col = 0; col < tetromino.GetSide(); ++col)
        {
            i32 value = tetromino.GetValue(row, col, m_rotation);
            if (value)
            {
                i32 boardRow = m_rowOffset + row;
                i32 boardCol = m_colOffset + col;
                
                if (boardRow < 0 || boardRow >= m_board->GetBoardRows() ||
                    boardCol < 0 || boardCol >= m_board->GetBoardCols() ||
                    m_board->GetCellValue(boardRow, boardCol))
                {
                    return false;
                }
            }
        }
    }
    
    return true;
}

void Piece::HardDrop()
{
    while (SoftDrop());
}

void Piece::MergeWithBoard()
{
    Tetromino tetromino = Tetromino::s_tetrominos[m_tetrominoIndex];
    
    for (i32 row = 0; row < tetromino.GetSide(); ++row)
    {
        for (i32 col = 0; col < tetromino.GetSide(); ++col)
        {
            i32 value = tetromino.GetValue(row, col, m_rotation);
            if (value)
            {
                i32 boardRow = m_rowOffset + row;
                i32 boardCol = m_colOffset + col;
                m_board->SetCellValue(boardRow, boardCol, value);
            }
        }
    }
}

bool Piece::SoftDrop()
{
    ++m_rowOffset;
    if (!IsValid())
    {
        --m_rowOffset;
        MergeWithBoard();
        SpawnNewPiece();
        
        return false;
    }
    
    m_time->nextDropTime = m_time->time + m_stats->GetTimeToNextDrop();
    return true;
}

void Piece::SpawnNewPiece()
{
    m_tetrominoIndex = random_int(0, Tetromino::s_numberOfTetrominos - 1);
    m_colOffset = m_board->GetBoardCols() / 2 - 1;
    m_rowOffset = 0;
    m_rotation = 0;
    m_time->nextDropTime = m_time->time + m_stats->GetTimeToNextDrop();
}

void Piece::DrawPiece(i32 t_xOffset, i32 t_yOffset, bool outline)
{
    Tetromino tetromino = Tetromino::s_tetrominos[m_tetrominoIndex];
    
    for (i32 row = 0; row < tetromino.GetSide(); ++row)
    {
        for (i32 col = 0; col < tetromino.GetSide(); ++col)
        {
            i32 value = tetromino.GetValue(row, col, m_rotation);
            if (value)
            {
                m_board->DrawCell(row + m_rowOffset, col + m_colOffset, value, t_xOffset, t_yOffset, outline);
            }
        }
    }
}