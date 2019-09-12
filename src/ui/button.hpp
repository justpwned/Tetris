#ifndef BUTTON_HPP
#define BUTTON_HPP

#include "../color.hpp"
#include "SDL_ttf.h"

namespace core
{
    namespace ui
    {
        enum ButtonState
        {
            BUTTON_OUT_FOCUS,
            BUTTON_IN_FOCUS
        };
        
        class Button
        {
            private:
            
            i32 m_buttonWidth;
            i32 m_buttonHeight;
            
            TTF_Font *m_buttonFont;
            const char* m_buttonLabel;
            Color m_buttonTextColor;
            
            ButtonState m_state;
            
            Color m_colorOutFocus;
            Color m_colorInFocus;
            
            public:
            
            Button() {}
            
            Button(i32 t_width, i32 t_height, TTF_Font *t_font, const char *t_label, ButtonState t_initialState, Color t_colorOutFocus, Color t_colorInFocus, Color t_textColor)
                : m_buttonWidth(t_width), m_buttonHeight(t_height), m_buttonFont(t_font), m_buttonLabel(t_label), m_state(t_initialState), m_colorOutFocus(t_colorOutFocus), m_colorInFocus(t_colorInFocus), m_buttonTextColor(t_textColor) {}
            
            void Render(i32 t_xOffset, i32 t_yOffset);
            
            inline i32 GetButtonWidth() const { return m_buttonWidth; }
            inline i32 SetButtonWidth(i32 t_width) { m_buttonWidth = t_width; }
            
            inline i32 GetButtonHeight() const { return m_buttonHeight; }
            inline i32 SetButtonHeight(i32 t_height) { m_buttonHeight = t_height; }
            
            inline const char* GetButtonLable() const { return m_buttonLabel; }
            inline void SetButtonLable(const char* t_label)  { m_buttonLabel = t_label; }
            
            inline ButtonState GetButtonState() const { return m_state; }
            inline void SetButtonState(ButtonState t_state) { m_state = t_state; }
        };
    }
}

#endif