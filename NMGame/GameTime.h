#pragma once
#include <Windows.h>

class GameTime
{
public:
    void StartCounter();
    float GetCouter();
    static GameTime* GetInstance();
    GameTime();
    ~GameTime();

private:
    LARGE_INTEGER mStartTime, mEndTime, mDelta, mClockRate;
    static GameTime* mInstance;
};


