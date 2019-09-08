#ifndef COLOR_H
#define COLOR_H

#include "utils.h"

namespace core
{
    class Color
    {
        public:
        
        u8 r;
        u8 g;
        u8 b;
        u8 a;
        
        Color() {}
        
        Color(u8 r, u8 g, u8 b, u8 a)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = a;
        }
        
        Color(u8 r, u8 g, u8 b)
        {
            this->r = r;
            this->g = g;
            this->b = b;
            this->a = 255;
        }
    };
}

#endif