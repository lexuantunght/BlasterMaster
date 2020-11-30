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
}

void EndingScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x1E1E1E;
    isReplace = false;
    mIsPlaySound = false;

    mAnimationDestroy = new DestroyAnimation("Assets/mountainDestroy.png", 2, 1, 2, 0.15f);
    mAnimationHead = new Animation("Assets/head.png", 3, 1, 3, 0.1f);
    mAnimationMountain = new MountainAnimation("Assets/mountain.png", 4, 1, 4, 0.75f);
    mBackground = new Sprite("Assets/ending.png");

    mAnimationDestroy->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
    mAnimationHead->SetPosition(894, 210);
    mAnimationMountain->SetPosition(GameGlobal::GetWidth() / 2 + 6, GameGlobal::GetHeight() / 2 + 32);
    mBackground->SetPosition(547.5f, 240);
}

void EndingScene::Update(float dt)
{
    mAnimationDestroy->Update(dt);
    if (mTimeCounter <= 5)
        mAnimationMountain->Update(dt);
    if (mTimeCounter >= 9 && mBackground->GetPosition().x > -67.5f)
    {
        if (!mIsPlaySound)
        {
            GameSound::GetInstance()->Play("Assets/Sounds/area_ending.mp3");
            mIsPlaySound = true;
        }
        mBackground->SetPosition(mBackground->GetPosition().x - 1, mBackground->GetPosition().y);
        mAnimationHead->SetPosition(mAnimationHead->GetPosition().x - 1, mAnimationHead->GetPosition().y);
    }
    mAnimationHead->Update(dt);
    mTimeCounter += dt;
}

void EndingScene::Draw()
{
    if (mTimeCounter <= 7)
        mAnimationDestroy->Draw();
    if (mTimeCounter <= 5)
        mAnimationMountain->Draw();
    if (mTimeCounter > 7)
        mBackground->Draw();
    mAnimationHead->Draw();
}