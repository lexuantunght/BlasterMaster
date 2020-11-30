#include "EndingScene.h"
#include "DestroyAnimation.h"
#include "MountainAnimation.h"
#include "../GameSound.h"

EndingScene::EndingScene()
{
    LoadContent();
    mTimeCounter = 0;
}

EndingScene::~EndingScene()
{
    delete mAnimationDestroy;
    delete mAnimationHead;
    delete mAnimationMountain;
    delete mBackground;
    delete mBackgroundEnd;
    delete mTextEnd;
    delete mTextScroll;
}

void EndingScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0xffffff;
    isReplace = false;
    mIsPlaySound = false;

    mAnimationDestroy = new DestroyAnimation("Assets/mountainDestroy.png", 2, 1, 2, 0.15f);
    mAnimationHead = new Animation("Assets/head.png", 3, 1, 3, 0.1f);
    mAnimationMountain = new MountainAnimation("Assets/mountain.png", 4, 1, 4, 0.75f);
    mBackground = new Sprite("Assets/ending.png");
    mBackgroundEnd = new Sprite("Assets/endingScroll.png");
    mTextScroll = new Sprite("Assets/textScroll.png");
    mTextEnd = new Sprite("Assets/textEnd.png");

    mAnimationDestroy->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
    mAnimationHead->SetPosition(781, 209);
    mAnimationMountain->SetPosition(GameGlobal::GetWidth() / 2 + 6, GameGlobal::GetHeight() / 2 + 32);
    mBackground->SetPosition(479, 240);
    mBackgroundEnd->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
    mTextScroll->SetPosition(340, 920);
    mTextEnd->SetPosition(340, 240);
}

void EndingScene::Update(float dt)
{
    if (mTimeCounter <= 5)
        mAnimationMountain->Update(dt);
    mAnimationDestroy->Update(dt);
    if ((mTimeCounter >= 9 && mTimeCounter < 38) && mBackground->GetPosition().x > 1)
    {
        if (!mIsPlaySound)
        {
            GameSound::GetInstance()->Play("Assets/Sounds/area_ending.mp3");
            mIsPlaySound = true;
        }
        mBackground->SetPosition(mBackground->GetPosition().x - 1, mBackground->GetPosition().y);
        mAnimationHead->SetPosition(mAnimationHead->GetPosition().x - 1, mAnimationHead->GetPosition().y);
    }
    if ((mTimeCounter >= 38 && mTimeCounter < 90) && mTextScroll->GetPosition().y > -440)
    {
        mTextScroll->SetPosition(mTextScroll->GetPosition().x, mTextScroll->GetPosition().y - 0.5);
    }
    mAnimationHead->Update(dt);
    mTimeCounter += dt;
}

void EndingScene::Draw()
{
    if (mTimeCounter <= 5)
        mAnimationMountain->Draw();
    if (mTimeCounter <= 7)
        mAnimationDestroy->Draw();
    if (mTimeCounter > 7 && mTimeCounter < 38)
    {
        mBackground->Draw();
        mAnimationHead->Draw();
    }
    if (mTimeCounter >= 38)
    {
        mBackgroundEnd->Draw();
        if (mTimeCounter < 90) mTextScroll->Draw();
        else mTextEnd->Draw();
    }
}