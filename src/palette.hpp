#ifndef PALETTE_HPP
#define PALETTE_HPP

#include "color.hpp"

namespace core
{
    class Palette
    {
        public:
        
        static const i32 s_size = 8;
        
        static const Color s_base[Palette::s_size];
        static const Color s_light[Palette::s_size];
        static const Color s_dark[Palette::s_size];
        
        static const Color s_highlightColor;
    };
}

#endif