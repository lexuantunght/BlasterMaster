#pragma once
#include "../Scene.h"
#include "../Animation.h"
#include <map>

class EndingScene : public Scene
{
public:
    EndingScene();
    ~EndingScene();

    void Update(float dt);
    virtual void LoadContent();
    void Draw();

    //void OnKeyDown(int keyCode);
    //void OnKeyUp(int keyCode);
    //void OnMouseDown(float x, float y);

protected:
    Animation* mAnimationHead, * mAnimationDestroy, * mAnimationMountain;
    Sprite* mBackground;

    bool mIsPlaySound;

    float mTimeCounter;

    std::map<int, bool> keys;
};

