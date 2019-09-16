#include "info.hpp"
#include "graphics/graphics.hpp"
#include "palette.hpp"
#include <iostream>
#include <fstream>

using namespace core;
using namespace core::graphics;

Info::Info(InputState *t_input, TTF_Font *t_font, const char *t_filename) 
: m_input(t_input), m_font(t_font)
{
    std::string line;
    std::ifstream infoFile(t_filename);
    
    if (infoFile.is_open())
    {
        while (std::getline(infoFile, line))
        {
            m_textLines.push_back(line);
        }
        
        infoFile.close();
    }
    else
    {
        std::cerr << "Unable to open file: " << t_filename << "\n";
    }
}

GamePhase Info::Update()
{
    if (m_input->descape > 0)
    {
        return GAME_PHASE_MENU;
    }
    
    return GAME_PHASE_INFO;
}

void Info::Render(i32 t_xOffset, i32 t_yOffset)
{
    Graphics::Instance()->DrawText(m_font, m_textLines[0].c_str(), t_xOffset, t_yOffset, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
    t_yOffset += 50;
    
    for (size_t i = 1; i < m_textLines.size(); ++i)
    {
        Graphics::Instance()->DrawText(m_font, m_textLines[i].c_str(), t_xOffset, t_yOffset, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
        t_yOffset += 30;
    }
}