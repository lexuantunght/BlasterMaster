#include "IntroAnimation.h"

IntroAnimation::~IntroAnimation()
{

}

void IntroAnimation::Update(float dt)
{
    if (mTotalFrame <= 1)
        return;

    if (mCurrentIndex == 3 || mCurrentIndex == 7 || mCurrentIndex == 11 || mCurrentIndex == 32 || mCurrentIndex == 36 || mCurrentIndex == 40 || mCurrentIndex == 44)
    {
        if (timeWait < 4)
        {
            timeWait += dt;
            return;
        }
        else
        {
            timeWait = 0;
            mCurrentTotalTime = mTimePerFrame;
        }
    }

    if (mCurrentIndex == 25)
    {
        if (timeWait < 1.0f)
        {
            timeWait += dt;
            return;
        }
        else
        {
            timeWait = 0;
            mCurrentTotalTime = mTimePerFrame;
        }
    }

    if (mCurrentTotalTime >= mTimePerFrame)
    {
        mCurrentTotalTime = 0;
        mCurrentIndex++;
        mCurrentColumn++;

        if (mCurrentIndex >= mTotalFrame)
        {
            mCurrentIndex = 0;
            mCurrentColumn = 0;
            mCurrentRow = 0;
        }

        if (mCurrentColumn >= mColumns)
        {
            mCurrentColumn = 0;
            mCurrentRow++;

            if (mCurrentRow >= mRows)
                mCurrentRow = 0;
        }

        mRect.left = mCurrentColumn * mFrameWidth;
        mRect.right = mRect.left + mFrameWidth;
        mRect.top = mCurrentRow * mFrameHeight;
        mRect.bottom = mRect.top + mFrameHeight;

        SetSourceRect(mRect);
    }
    else
    {
        mCurrentTotalTime += dt;
    }
}
