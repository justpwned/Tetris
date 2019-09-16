#include "menu.hpp"
#include "palette.hpp"

using namespace core;
using namespace core::ui;

Menu::Menu(InputState *t_input, TTF_Font *t_font) : m_input(t_input)
{
    Color outFocusColor = Color(0xad, 0x7f, 0x00);
    Color inFocusColor = Color(0xfc, 0xba, 0x03);
    Color textColor = Palette::s_highlightColor;
    
    m_buttons = std::vector<Button>();
    m_menuState = MENU_PLAY;
    
    m_buttons.push_back(Button(BUTTON_WIDTH, BUTTON_HEIGHT, t_font, "Play", 
                               ui::BUTTON_OUT_FOCUS, outFocusColor, inFocusColor, textColor));
    
    m_buttons.push_back(Button(BUTTON_WIDTH, BUTTON_HEIGHT, t_font, "Highscores",
                               ui::BUTTON_OUT_FOCUS, outFocusColor, inFocusColor, textColor));
    
    m_buttons.push_back(Button(BUTTON_WIDTH, BUTTON_HEIGHT, t_font, "Info",
                               ui::BUTTON_OUT_FOCUS, outFocusColor, inFocusColor, textColor));
    
    m_buttons.push_back(Button(BUTTON_WIDTH, BUTTON_HEIGHT, t_font, "Exit",
                               ui::BUTTON_OUT_FOCUS, outFocusColor, inFocusColor, textColor));
    
    m_buttons[m_menuState].SetState(BUTTON_IN_FOCUS);
}

GamePhase Menu::Update()
{
    if (m_input->ddown > 0)
    {
        m_buttons[m_menuState].SetState(BUTTON_OUT_FOCUS);
        m_menuState = (MenuState)((m_menuState + 1) % m_buttons.size());
        m_buttons[m_menuState].SetState(BUTTON_IN_FOCUS);
    }
    
    if (m_input->dup > 0)
    {
        m_buttons[m_menuState].SetState(BUTTON_OUT_FOCUS);
        m_menuState = (MenuState)((m_menuState - 1) % m_buttons.size());
        m_buttons[m_menuState].SetState(BUTTON_IN_FOCUS);
    }
    
    if (m_input->denter > 0)
    {
        switch (m_menuState)
        {
            case MENU_PLAY:
            {
                return GAME_PHASE_START;
            } break;
            
            case MENU_HIGHSCORES:
            {
                return GAME_PHASE_HIGHSCORES;
            } break;
            
            case MENU_INFO:
            {
                return GAME_PHASE_INFO;
            } break;
            
            case MENU_EXIT:
            {
                return GAME_PHASE_EXIT;
            } break;
        }
    }
    
    return GAME_PHASE_MENU;
}

void Menu::Render(i32 t_xOffset, i32 t_yOffset, ButtonAlign t_buttonAlign)
{
    for (size_t buttonIndex = 0; buttonIndex < m_buttons.size(); ++buttonIndex)
    {
        i32 xOffset = t_xOffset;
        switch (t_buttonAlign)
        {
            case BUTTON_ALIGN_LEFT:
            {
                xOffset = t_xOffset;
            } break;
            
            case BUTTON_ALIGN_CENTER:
            {
                xOffset = t_xOffset - m_buttons[buttonIndex].GetWidth() / 2;
            } break;
            
            case BUTTON_ALIGN_RIGHT:
            {
                xOffset = t_xOffset - m_buttons[buttonIndex].GetWidth();
            } break;
        }
        
        i32 yOffset = t_yOffset + 
            (i32)(m_buttons[buttonIndex].GetHeight() * 1.5f * buttonIndex);
        m_buttons[buttonIndex].Render(xOffset, yOffset);
    }
}