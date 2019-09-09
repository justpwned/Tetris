#include "board.hpp"
#include "palette.hpp"
#include "graphics\graphics.hpp"

using namespace core;
using namespace core::gameplay;
using namespace core::graphics;

Board::Board(i32 t_boardRows, i32 t_boardCols, i32 t_boardVisibleRows, i32 t_boardGridSize)
{
    m_boardRows = t_boardRows;
    m_boardCols = t_boardCols;
    m_boardVisibleRows = t_boardVisibleRows;
    m_boardGridSize = t_boardGridSize;
    m_boardData.Resize(t_boardRows, t_boardCols);
}

void Board::DrawCell(i32 t_row, i32 t_col, i32 t_value, i32 t_xOffset, i32 t_yOffset, bool t_outline)
{
    Color baseColor = Palette::s_base[t_value];
    Color lightColor = Palette::s_light[t_value];
    Color darkColor = Palette::s_dark[t_value];
    
    i32 edgeSize = m_boardGridSize / 8;
    
    i32 x = t_col * m_boardGridSize + t_xOffset;
    i32 y = t_row * m_boardGridSize + t_yOffset;
    
    if (t_outline)
    {
        Graphics::Instance()->DrawRect(x, y, m_boardGridSize, m_boardGridSize, baseColor);
    }
    else
    {
        Graphics::Instance()->DrawFillRect(x, y, m_boardGridSize, m_boardGridSize, darkColor);
        Graphics::Instance()->DrawFillRect(x + edgeSize, y, m_boardGridSize - edgeSize, m_boardGridSize - edgeSize, lightColor);
        Graphics::Instance()->DrawFillRect(x + edgeSize, y + edgeSize, m_boardGridSize - edgeSize * 2, m_boardGridSize - edgeSize * 2, baseColor);
    }
}

void Board::DrawBoard(i32 t_xOffset, i32 t_yOffset)
{
    Graphics::Instance()->DrawFillRect(t_xOffset, t_yOffset, m_boardCols * m_boardGridSize, m_boardRows * m_boardGridSize, Palette::s_base[0]);
    
    for (i32 row = 0; row < m_boardRows; ++row)
    {
        for (i32 col = 0; col < m_boardCols; ++col)
        {
            i32 value = GetCellValue(row, col);
            if (value)
            {
                DrawCell(row, col, value, t_xOffset, t_yOffset);
            }
        }
    }
}