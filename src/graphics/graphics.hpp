#ifndef GRAPHICS_H
#define GRAPHICS_H

#include "SDL.h"
#include "SDL_ttf.h"
#include "../color.hpp"

namespace core
{
    namespace graphics
    {
        enum TextAlign
        {
            TEXT_ALIGN_LEFT,
            TEXT_ALIGN_CENTER,
            TEXT_ALIGN_RIGHT
        };
        
        class Graphics
        {
            private:
            
            SDL_Renderer *m_renderer;
            i32 m_windowWidth;
            i32 m_windowHeight;
            
            Graphics() {}
            ~Graphics() {}
            
            static Graphics* s_instance;
            
            public:
            
            static Graphics* Instance();
            
            inline void SetRenderer(SDL_Renderer *t_renderer) { m_renderer = t_renderer; }
            inline SDL_Renderer* GetRenderer() const { return m_renderer; }
            
            void DrawFillRect(i32 t_x, i32 t_y, i32 t_width, i32 t_height, Color t_color);
            void DrawRect(i32 t_x, i32 t_y, i32 t_width, i32 t_height, Color t_color);
            void DrawText(TTF_Font *t_font, const char *t_text, i32 t_x, i32 t_y,
                          TextAlign t_alignment, Color t_color);
            void FillBackground(Color t_color);
        };
    }
}

#endif