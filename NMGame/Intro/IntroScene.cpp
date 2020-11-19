#include "IntroScene.h"
#include "../Scenes/FirstScene.h"
#include "../SceneManager.h"

IntroScene::IntroScene()
{
    LoadContent();
    mTimeCounter = 0;
}

void IntroScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x1E1E1E;
    isReplace = false;

    mAnimationTitle = new TitleAnimation("Assets/title.png", 5, 1, 5, 0.1f);
    mAnimationIntro = new IntroAnimation("Assets/intro.png", 48, 12, 4, 0.1f);
    mAnimationSophia = new SophiaAnimation("Assets/rollout.png", 12, 4, 3, 0.2f);

    mAnimationTitle->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
    mAnimationIntro->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
    mAnimationSophia->SetPosition(GameGlobal::GetWidth() / 2, GameGlobal::GetHeight() / 2);
    mCurrentAnimation = mAnimationTitle;
}

void IntroScene::Update(float dt)
{
    if (mTimeCounter >= 5.0f)
    {
        mCurrentAnimation = mAnimationIntro;
    }
    if (mTimeCounter >= 38.0f)
    {
        mCurrentAnimation = mAnimationSophia;
    }
    if (mTimeCounter >= 43.0f)
    {
        SceneManager::GetInstance()->ReplaceScene(new FirstScene());
        return;
    }
    mCurrentAnimation->Update(dt);
    mTimeCounter += dt;
}

void IntroScene::Draw()
{
    mCurrentAnimation->Draw();
}