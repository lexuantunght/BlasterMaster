#include "TitleAnimation.h"

TitleAnimation::~TitleAnimation()
{

}

void TitleAnimation::Update(float dt)
{
    if (mTotalFrame <= 1)
        return;
    if (timeLoad >= 2.9f)
        return;

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

    timeLoad += dt;
}

void TitleAnimation::Reset()
{
    Animation::Reset();
    timeLoad = 0;
}