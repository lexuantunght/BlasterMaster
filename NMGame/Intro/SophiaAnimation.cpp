#include "SophiaAnimation.h"

SophiaAnimation::~SophiaAnimation()
{

}

void SophiaAnimation::Update(float dt)
{
    if (mTotalFrame <= 1)
        return;

    if (mCurrentIndex == 1)
    {
        if (timeWait < 1)
        {
            if (mCurrentTotalTime >= mTimePerFrame)
            {
                mCurrentIndex = -1;
                mCurrentColumn = -1;
            }
            timeWait += dt;
        }
        else
        {
            timeWait = 0;
            mCurrentTotalTime = mTimePerFrame;
        }
    }

    if (mCurrentIndex == 11)
    {
        return;
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
