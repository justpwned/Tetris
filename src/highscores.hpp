#ifndef HIGHSCORES_HPP
#define HIGHSCORES_HPP

#include <vector>
#include "game_utils.hpp"
#include "SDL_ttf.h"

#define MAX_NAME_LENGTH 16

namespace core
{
    struct HighscoreHeader
    {
        i32 nameLength;
        char name[MAX_NAME_LENGTH];
        i32 score;
    };
    
    class Highscores
    {
        private:
        
        InputState *m_input;
        TTF_Font *m_font;
        const char *m_filename;
        
        i32 m_numberOfRecords = 5;
        std::vector<HighscoreHeader*> m_records = std::vector<HighscoreHeader*>(m_numberOfRecords);
        
        public:
        
        Highscores() {}
        
        Highscores(InputState *t_input, TTF_Font *t_font, const char *t_filename) 
            : m_input(t_input), m_font(t_font), m_filename(t_filename) {}
        
        void LoadRecords();
        void DumpRecords();
        bool WriteRecord(const char *t_name, i32 t_score);
        
        GamePhase Update();
        void Render(i32 t_xOffset, i32 t_yOffset);
    };
}

#endif