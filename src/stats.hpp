#ifndef STATS_HPP
#define STATS_HPP

#include "common_utils.h"
#include "game_utils.h"

namespace core
{
    namespace gameplay
    {
        class Stats
        {
            private:
            
            bool m_lines[BOARD_ROWS];
            
            i32 m_pendingLineCount = 0;
            i32 m_startLevel = 0;
            i32 m_level = 0;
            i32 m_lineCount = 0;
            i32 m_points = 0;
            
            public:
            
            Stats() {}
            
            void ComputePoints();
            i32 GetLinesForNextLevel();
            f32 GetTimeToNextDrop();
            
            inline bool* GetLines() { return m_lines; }
            inline i32 GetPendingLineCount() { return m_pendingLineCount; }
            inline i32 GetStartLevel() { return m_startLevel; }
            inline i32 GetLevel() { return m_level; }
            inline i32 GetLineCount() { return m_lineCount; }
            inline i32 GetPoints() { return m_points; }
            
            inline void SetPendingLineCount(i32 t_pendingLineCount) { m_pendingLineCount = t_pendingLineCount; }
            
            inline void SetStartLevel(i32 t_startLevel) { m_startLevel = t_startLevel;  }
            inline void SetLevel(i32 t_level) { m_level = t_level; }
            inline void SetLineCount(i32 t_lineCount) { m_lineCount = t_lineCount; }
            inline void SetPoints(i32 t_points) { m_points = t_points; }
        };
    }
}

#endif