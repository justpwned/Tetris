#include "graphics.hpp"

using namespace core;
using namespace core::graphics;

Graphics* Graphics::s_instance = nullptr;

Graphics* Graphics::Instance()
{
    if (!s_instance)
    {
        s_instance = new Graphics();
    }
    
    return s_instance;
}

void Graphics::FillBackground(Color t_color)
{
    SDL_SetRenderDrawColor(m_renderer, t_color.r, t_color.g, t_color.b, t_color.a);
    SDL_RenderClear(m_renderer);
}

void Graphics::DrawFillRect(i32 t_x, i32 t_y, i32 t_width, i32 t_height, Color t_color)
{
    SDL_Rect rect = { t_x, t_y, t_width, t_height };
    SDL_SetRenderDrawColor(m_renderer, t_color.r, t_color.g, t_color.b, t_color.a);
    SDL_RenderFillRect(m_renderer, &rect);
}

void Graphics::DrawRect(i32 t_x, i32 t_y, i32 t_width, i32 t_height, Color t_color)
{
    SDL_Rect rect = { t_x, t_y, t_width, t_height };
    SDL_SetRenderDrawColor(m_renderer, t_color.r, t_color.g, t_color.b, t_color.a);
    SDL_RenderDrawRect(m_renderer, &rect);
}

void Graphics::DrawText(TTF_Font *t_font, const char *t_text, i32 t_x, i32 t_y,
                        TextAlign t_alignment, Color t_color)
{
    SDL_Color color = { t_color.r, t_color.g, t_color.b };
    SDL_Surface *textSurface = TTF_RenderText_Blended(t_font, t_text, color);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    
    SDL_Rect destRect = { t_x, t_y, textSurface->w, textSurface->h };
    
    switch (t_alignment)
    {
        case TEXT_ALIGN_LEFT:
        {
            destRect.x = t_x;
        } break;
        
        case TEXT_ALIGN_CENTER:
        {
            destRect.x = t_x - textSurface->w / 2;
        } break;
        
        case TEXT_ALIGN_RIGHT:
        {
            destRect.x = t_x - textSurface->w;
        } break;
    }
    
    SDL_RenderCopy(m_renderer, textTexture, 0, &destRect);
    
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
}