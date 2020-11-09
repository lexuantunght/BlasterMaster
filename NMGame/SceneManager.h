#pragma once
#include <vector>
#include "Scene.h"

class SceneManager
{
public:
    static SceneManager* GetInstance();
    SceneManager();
    ~SceneManager();

    Scene* GetCurrentScene();
    void Update(float dt);
    void ReplaceScene(Scene* scene);

private:
    static SceneManager* mInstace;
    Scene* mCurrentScene;
};