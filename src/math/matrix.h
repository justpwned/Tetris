#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cassert>
#include "utils.h"

// TODO(Kirill): Test operator overloading, write * overloading

namespace math
{
    class Matrix
    {
        private:
        
        i32 m_rows;
        i32 m_cols;
        std::vector<i32> m_data;
        
        public:
        
        Matrix(i32 rows, i32 cols)
        {
            m_rows = rows;
            m_cols = cols;
            m_data = std::vector<i32>(rows * cols);
        }
        
        inline i32 getCols() const
        {
            return m_cols;
        }
        
        inline i32 getRows() const 
        {
            return m_rows;
        }
        
        inline i32 getValue(i32 row, i32 col) const
        {
            assert(row >= 0 && row < m_rows && col >=0 && col < m_cols);
            return m_data[row * m_rows + col];
        }
        
        inline void setValue(i32 row, i32 col, i32 value)
        {
            assert(row >= 0 && row < m_rows && col >=0 && col < m_cols);
            m_data[row * m_rows + col] = value;
        }
        
        inline Matrix operator+(const Matrix& other) const
        {
            assert(m_rows == other.m_rows && m_cols == other.m_cols);
            
            Matrix ret(m_rows, m_cols);
            for (i32 y = 0; y < m_rows; y++)
            {
                for (i32 x = 0; x < m_cols; x++)
                {
                    ret.setValue(y, x, getValue(y, x) + other.getValue(y, x));
                }
            }
            
            return ret;
        }
        
        inline Matrix& operator+=(const Matrix& other) 
        {
            assert(m_rows == other.m_rows && m_cols == other.m_cols);
            
            for (i32 y = 0; y < m_rows; y++)
            {
                for (i32 x = 0; x < m_cols; x++)
                {
                    setValue(y, x, getValue(y, x) + other.getValue(y, x));
                }
            }
            
            return *this;
        }
    };
    
    typedef Matrix mat;
}

#endif
