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
            
            public:
            
            Graphics() {}
            
            Graphics(SDL_Renderer *t_renderer)
                : m_renderer(t_renderer) { }
            
            void DrawFillRect(i32 t_x, i32 t_y, i32 t_width, i32 t_height, Color t_color);
            void DrawRect(i32 t_x, i32 t_y, i32 t_width, i32 t_height, Color t_color);
            void DrawString(TTF_Font *t_font, const char *t_text, i32 t_x, i32 t_y,
                            TextAlign t_alignment, Color t_color);
        };
    }
}

#endif