#include "IntroScene.h"
#include "../Scenes/FirstScene.h"
#include "../SceneManager.h"
#include "../GameSound.h"

IntroScene::IntroScene()
{
    LoadContent();
    mTimeCounter = 0;
}

IntroScene::~IntroScene()
{
    delete mAnimationSophia;
    delete mAnimationIntro;
    delete mAnimationTitle;
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
    if (mTimeCounter >= 5.0f && mTimeCounter < 38)
    {
        if (mCurrentAnimation != mAnimationIntro)
        {
            GameSound::GetInstance()->Play("Assets/Sounds/intro.mp3");
            mCurrentAnimation = mAnimationIntro;
        }
    }
    if (mTimeCounter >= 38 && mTimeCounter < 41)
    {
        if (mCurrentAnimation != mAnimationTitle)
        {
            mAnimationTitle->Reset();
            mCurrentAnimation = mAnimationTitle;
        }
    }
    if (mTimeCounter >= 41.0f && mTimeCounter < 46)
    {
        if (mCurrentAnimation != mAnimationSophia)
        {
            GameSound::GetInstance()->Close("intro");
            GameSound::GetInstance()->Play("Assets/Sounds/intro2.mp3");
            mCurrentAnimation = mAnimationSophia;
        }
    }
    if (mTimeCounter >= 46.0f)
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