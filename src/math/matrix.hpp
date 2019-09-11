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
            std::vector<i32> m_data = std::vector<i32>();
            
            public:
            
            Matrix() {}
            
            Matrix(i32 t_rows, i32 t_cols)
            {
                m_rows = t_rows;
                m_cols = t_cols;
                Resize(t_rows, t_cols);
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
                Clear();
            }
            
            void Clear()
            {
                std::fill(m_data.begin(), m_data.end(), 0);
            }
            
            void SetElements(i32 t_startIndex, i32 t_endIndex, i32 t_value)
            {
                std::fill(m_data.begin() + t_startIndex,
                          m_data.begin() + t_endIndex,
                          t_value);
            }
            
            void CopyElements(i32 t_destIndex, i32 t_srcIndex, i32 t_length)
            {
                std::copy(m_data.begin() + t_srcIndex,
                          m_data.begin() + t_srcIndex + t_length,
                          m_data.begin() + t_destIndex);
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
