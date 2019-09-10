#include "piece.hpp"

using namespace core::gameplay;

static const i32 FRAMES_PER_DROP[] = {
    48,
    43,
    38,
    33,
    28,
    23,
    18,
    13,
    8,
    6,
    5,
    5,
    5,
    4,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    1
};

bool Piece::IsValid()
{
    return true;
}

bool Piece::SoftDrop()
{
    return true;
}

f32 Piece::GetTimeToNextDrop(i32 t_level)
{
    i32 level = MIN(29, t_level);
    f32 targetSecondsPerFrame = 1.0f / 60.0f;
    return FRAMES_PER_DROP[level] * targetSecondsPerFrame;
}

void Piece::SpawnNewPiece(GameState *t_gameState)
{
    m_tetrominoIndex = random_int(0, Tetromino::s_numberOfTetrominos - 1);
    m_colOffset = m_board->GetBoardCols() / 2 - 1;
    m_rowOffset = 0;
    m_rotation = 0;
    t_gameState->nextDropTime = t_gameState->time + GetTimeToNextDrop(t_gameState->level);
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