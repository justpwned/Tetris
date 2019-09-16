#ifndef INFO_HPP
#define INFO_HPP

#include <string>
#include <vector>

#include "game_utils.hpp"
#include "SDL_ttf.h"

namespace core
{
    class Info
    {
        private:
        
        InputState *m_input;
        TTF_Font *m_font;
        std::vector<std::string> m_textLines;
        
        public:
        
        Info() {}
        
        Info(InputState *t_input, TTF_Font *t_font, const char *t_filename);
        
        GamePhase Update();
        void Render(i32 t_xOffset, i32 t_yOffset);
    };
}

#endif