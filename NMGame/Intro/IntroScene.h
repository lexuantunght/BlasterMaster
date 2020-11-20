#pragma once
#include "../Scene.h"
#include "TitleAnimation.h"
#include "IntroAnimation.h"
#include "SophiaAnimation.h"
#include <map>
class IntroScene : public Scene
{
public:
    IntroScene();
    ~IntroScene();

    void Update(float dt);
    virtual void LoadContent();
    void Draw();

    //void OnKeyDown(int keyCode);
    //void OnKeyUp(int keyCode);
    //void OnMouseDown(float x, float y);

protected:
    Animation* mAnimationTitle, * mAnimationIntro, * mAnimationSophia, * mCurrentAnimation;

    float mTimeCounter;

    std::map<int, bool> keys;
};

