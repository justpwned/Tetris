#ifndef MENU_HPP
#define MENU_HPP

#include "game_utils.h"
#include "ui/button.hpp"

namespace core
{
    enum ButtonOnFocus
    {
        PLAY_BUTTON,
        HIGHSCORE_BUTTON,
        EXIT_BUTTON,
        TOTAL_BUTTON
    };
    
    class Menu
    {
        private:
        
        InputState *m_input;
        
        public:
        
        Menu() {}
        
        Menu(InputState *t_input)
            : m_input(t_input) {}
        
        void Update();
        void Render(i32 t_xOffset, i32 t_yOffset);
    };
}

#endif