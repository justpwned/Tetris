#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <cassert>
#include "common_utils.h"

namespace core
{
    namespace math
    {
        class Matrix
        {
            private:
            
            i32 m_rows;
            i32 m_cols;
            std::vector<i32> m_data;
            
            public:
            
            Matrix() {}
            
            Matrix(i32 rows, i32 cols)
            {
                m_rows = rows;
                m_cols = cols;
                m_data = std::vector<i32>(rows * cols);
            }
            
            Matrix(i32 *data, i32 rows, i32 cols)
                : Matrix(rows, cols)
            {
                for (i32 r = 0; r < rows; r++)
                {
                    for (i32 c = 0; c < cols; c++)
                    {
                        SetValue(r, c, data[r * cols + c]);
                    }
                }
            }
            
            void Resize(i32 rows, i32 cols)
            {
                m_rows = rows;
                m_cols = cols;
                m_data.resize(rows * cols);
                m_data.clear();
            }
            
            void Clear()
            {
                m_data.clear();
            }
            
            inline i32 GetCols() const
            {
                return m_cols;
            }
            
            inline i32 GetRows() const 
            {
                return m_rows;
            }
            
            inline i32 GetValue(i32 row, i32 col) const
            {
                assert(row >= 0 && row < m_rows && col >=0 && col < m_cols);
                return m_data[row * m_cols + col];
            }
            
            inline void SetValue(i32 row, i32 col, i32 value)
            {
                assert(row >= 0 && row < m_rows && col >=0 && col < m_cols);
                m_data[row * m_cols + col] = value;
            }
            
            inline Matrix operator+(const Matrix& other) const
            {
                assert(m_rows == other.m_rows && m_cols == other.m_cols);
                
                Matrix ret(m_rows, m_cols);
                for (i32 y = 0; y < m_rows; y++)
                {
                    for (i32 x = 0; x < m_cols; x++)
                    {
                        ret.SetValue(y, x, GetValue(y, x) + other.GetValue(y, x));
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
                        SetValue(y, x, GetValue(y, x) + other.GetValue(y, x));
                    }
                }
                
                return *this;
            }
        };
        
        typedef Matrix mat;
    }
}

#endif
