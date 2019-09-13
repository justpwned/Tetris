#ifndef MENU_HPP
#define MENU_HPP

#include "SDL_ttf.h"
#include "game_utils.h"
#include "ui/button.hpp"
#include <vector>

namespace core
{
    enum MenuState
    {
        MENU_PLAY = 0,
        MENU_HIGHSCORES,
        MENU_INFO,
        MENU_EXIT
    };
    
    enum ButtonAlign
    {
        BUTTON_ALIGN_LEFT,
        BUTTON_ALIGN_CENTER,
        BUTTON_ALIGN_RIGHT
    };
    
    class Menu
    {
        private:
        
        InputState *m_input;
        
        std::vector<ui::Button> m_buttons;
        MenuState m_menuState;
        
        public:
        
        Menu() {}
        
        Menu(InputState *t_input, TTF_Font *t_font);
        
        GamePhase Update();
        void Render(i32 t_xOffset, i32 t_yOffset, ButtonAlign t_buttonAlign);
    };
}

#endif