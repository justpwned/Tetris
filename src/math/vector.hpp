#ifndef VECTOR_H
#define VECTOR_H

#include "../utils.h"

namespace math
{
    class Vector
    {
        private:
        
        i32 m_x;
        i32 m_y;
        
        public:
        
        Vector(i32 x, i32 y)
        {
            m_x = x;
            m_y = y;
        }
        
        inline i32 getX() const 
        {
            return m_x;
        }
        
        inline void setX(i32 x)
        {
            m_x = x;
        }
        
        inline i32 getY() const
        {
            return m_y;
        }
        
        inline void setY(i32 y)
        {
            m_y = y;
        }
        
        inline Vector operator+(const Vector& other) const
        {
            return Vector(m_x + other.getX(), m_y + other.getY());
        }
        
        inline Vector& operator+=(const Vector& other)
        {
            m_x += other.getX();
            m_y += other.getY();
            return *this;
        }
        
        inline Vector operator-(const Vector& other) const
        {
            return Vector(m_x - other.getX(), m_y - other.getY());
        }
        
        inline Vector& operator+=(const Vector& other)
        {
            m_x -= other.getX();
            m_y -= other.getY();
            return *this;
        }
    };
    
    typedef Vector vec2;
}

#endif