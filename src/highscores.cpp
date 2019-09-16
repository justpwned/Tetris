#include "highscores.hpp"
#include "graphics/graphics.hpp"
#include "palette.hpp"
#include <cstring>
#include <fstream>
#include <stdio.h>

using namespace core;
using namespace core::graphics;

void Highscores::LoadRecords()
{
    std::ifstream highscoresFile(m_filename, std::ios::in | std::ios::binary);
    i32 recordIndex = 0;
    
    while (highscoresFile.peek() != EOF && recordIndex < m_numberOfRecords)
    {
        HighscoreHeader *header = m_records[recordIndex];
        if (!header)
        {
            m_records[recordIndex] = new HighscoreHeader();
        }
        
        i32 nameLength;
        highscoresFile.read(reinterpret_cast<char*>(&nameLength), sizeof(i32));
        m_records[recordIndex]->nameLength = nameLength;
        highscoresFile.read(m_records[recordIndex]->name, nameLength);
        m_records[recordIndex]->name[nameLength] = '\0';
        highscoresFile.read(reinterpret_cast<char*>(&m_records[recordIndex]->score), sizeof(i32));
        
        ++recordIndex;
    }
}

void Highscores::DumpRecords()
{
    std::ofstream highscoreFile(m_filename, std::ios::out | std::ios::binary);
    for (size_t i = 0; i < m_records.size(); ++i)
    {
        HighscoreHeader *header = m_records[i];
        if (header)
        {
            i32 nameLength = header->nameLength;
            char *name = header->name;
            i32 score = header->score;
            
            highscoreFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
            highscoreFile.write(name, nameLength);
            highscoreFile.write(reinterpret_cast<char*>(&score), sizeof(score));
        }
    }
}

bool Highscores::WriteRecord(const char *t_name, i32 t_score)
{
    bool ret = false;
    for (size_t i = 0; i < m_records.size(); ++i)
    {
        HighscoreHeader *header = m_records[i];
        if(!header)
        {
            m_records[i] = new HighscoreHeader();
        }
        
        if (t_score > header->score)
        {
            m_records[i]->nameLength = strlen(t_name);
            strcpy(m_records[i]->name, t_name);
            m_records[i]->score = t_score;
            ret = true;
        }
    }
    
    if (ret)
    {
        DumpRecords();
    }
    
    return ret;
}

GamePhase Highscores::Update()
{
    if (m_input->descape > 0)
    {
        return GAME_PHASE_MENU;
    }
    
    return GAME_PHASE_HIGHSCORES;
}

void Highscores::Render(i32 t_xOffset, i32 t_yOffset)
{
    Graphics::Instance()->DrawText(m_font, "Highscores", t_xOffset, t_yOffset, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
    t_yOffset += 50;
    
    for (size_t i = 0; i < m_records.size(); ++i)
    {
        HighscoreHeader *header = m_records[i];
        if (header)
        {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%d. %s %d", i + 1, header->name, header->score);
            Graphics::Instance()->DrawText(m_font, buffer, 30, t_yOffset, TEXT_ALIGN_LEFT, Palette::s_highlightColor);
        }
        
        t_yOffset += 30;
    }
}