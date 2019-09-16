#include "button.hpp"
#include "../graphics/graphics.hpp"
#include "../palette.hpp"

using namespace core::ui;
using namespace core::graphics;

void Button::Render(i32 t_xOffset, i32 t_yOffset)
{
    Color color = m_state == BUTTON_OUT_FOCUS ? m_colorOutFocus : m_colorInFocus;
    Graphics::Instance()->DrawFillRect(t_xOffset, t_yOffset, m_buttonWidth, m_buttonHeight, color);
    
    i32 textWidth, textHeight;
    TTF_SizeText(m_buttonFont, m_buttonLabel, &textWidth, &textHeight);
    i32 xPos = t_xOffset + m_buttonWidth / 2;
    i32 yPos = t_yOffset + m_buttonHeight / 2 - textHeight / 2;
    Graphics::Instance()->DrawText(m_buttonFont, m_buttonLabel, xPos, yPos, TEXT_ALIGN_CENTER, m_buttonTextColor);
}