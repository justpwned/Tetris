#include "highscores.hpp"
#include "graphics/graphics.hpp"
#include "palette.hpp"
#include <cstring>
#include <fstream>
#include <stdio.h>

using namespace core;
using namespace core::graphics;

Highscores::Highscores(InputState *t_input, TTF_Font *t_font, const char *t_filename) 
: m_input(t_input), m_font(t_font), m_filename(t_filename) 
{
    for (size_t i = 0; i < m_numberOfRecords; ++i)
    {
        m_records.push_back(new HighscoreHeader());
    }
}

void Highscores::LoadRecords()
{
    std::ifstream highscoresFile(m_filename, std::ios::in | std::ios::binary);
    size_t recordIndex = 0;
    
    while (highscoresFile.peek() != EOF && recordIndex < m_numberOfRecords)
    {
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
        i32 nameLength = m_records[i]->nameLength;
        char *name = m_records[i]->name;
        i32 score = m_records[i]->score;
        
        highscoreFile.write(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));
        highscoreFile.write(name, nameLength);
        highscoreFile.write(reinterpret_cast<char*>(&score), sizeof(score));
    }
}

bool Highscores::WriteRecord(const char *t_name, i32 t_score)
{
    bool ret = false;
    for (size_t i = 0; i < m_records.size(); ++i)
    {
        if (t_score > m_records[i]->score)
        {
            for (size_t j = m_records.size() - 1; j > i; --j)
            {
                m_records[j]->nameLength = m_records[j - 1]->nameLength;
                strcpy(m_records[j]->name, m_records[j - 1]->name);
                m_records[j]->score = m_records[j - 1]->score;
            }
            
            m_records[i]->nameLength = strlen(t_name);
            strcpy(m_records[i]->name, t_name);
            m_records[i]->score = t_score;
            DumpRecords();
            
            return true;
        }
    }
    
    return false;
}

GamePhase Highscores::Update()
{
    if (m_input->descape > 0)
    {
        return GAME_PHASE_MENU;
    }
    
    return GAME_PHASE_HIGHSCORES;
}

bool Highscores::IsHighscore(i32 t_score)
{
    for (size_t i = 0; i < m_records.size(); ++i)
    {
        if (t_score > m_records[i]->score)
        {
            return true;
        }
    }
    
    return false;
}

void Highscores::Render(i32 t_xOffset, i32 t_yOffset)
{
    Graphics::Instance()->DrawText(m_font, "Highscores", t_xOffset, t_yOffset, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
    t_yOffset += 50;
    i32 recordsShown = 0;
    
    for (size_t i = 0; i < m_records.size(); ++i)
    {
        HighscoreHeader *header = m_records[i];
        if (header && header->score)
        {
            char buffer[32];
            snprintf(buffer, sizeof(buffer), "%d. %s %d", i + 1, header->name, header->score);
            Graphics::Instance()->DrawText(m_font, buffer, 30, t_yOffset, TEXT_ALIGN_LEFT, Palette::s_highlightColor);
            ++recordsShown;
        }
        
        t_yOffset += 30;
    }
    
    if (!recordsShown)
    {
        Graphics::Instance()->DrawText(m_font, "No highscores yet", t_xOffset, t_yOffset, TEXT_ALIGN_CENTER, Palette::s_highlightColor);
    }
}