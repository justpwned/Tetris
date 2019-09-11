#include "stats.hpp"

using namespace core::gameplay;

static const i32 FRAMES_PER_DROP[] = {
    48,
    43,
    38,
    33,
    28,
    23,
    18,
    13,
    8,
    6,
    5,
    5,
    5,
    4,
    4,
    4,
    3,
    3,
    3,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    2,
    1
};

f32 Stats::GetTimeToNextDrop()
{
    i32 level = MIN(29, m_level);
    f32 targetSecondsPerFrame = 1.0f / 60.0f;
    return FRAMES_PER_DROP[level] * targetSecondsPerFrame;
}

void Stats::ComputePoints()
{
    switch (m_lineCount)
    {
        case 1:
        {
            m_points += 40 * (m_level + 1);
        } break;
        
        case 2:
        {
            m_points += 100 * (m_level + 1);
        } break;
        
        case 3: 
        {
            m_points += 300 * (m_level + 1);
        } break;
        
        case 4:
        {
            m_points += 1200 * (m_level + 1);
        } break;
    }
}

i32 Stats::GetLinesForNextLevel()
{
    i32 firstLevelUpLimit = MIN(m_startLevel * 10 + 10, 
                                MAX(100, (m_startLevel * 10 - 50)));
    
    if (m_level == m_startLevel)
    {
        return firstLevelUpLimit;
    }
    
    i32 diff = m_level - m_startLevel;
    return firstLevelUpLimit;
}