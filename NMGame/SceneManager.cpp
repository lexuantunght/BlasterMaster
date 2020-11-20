#include "SceneManager.h"
#include "Scenes/FirstScene.h"
#include "Scenes/SecondScene.h"

SceneManager* SceneManager::mInstace = NULL;

SceneManager::SceneManager()
{
    mCurrentScene = nullptr;
}

SceneManager::~SceneManager()
{
}

SceneManager* SceneManager::GetInstance()
{
    if (!mInstace)
        mInstace = new SceneManager();

    return mInstace;
}

Scene* SceneManager::GetCurrentScene()
{
    return mCurrentScene;
}

void SceneManager::Update(float dt)
{
    mCurrentScene->Update(dt);
}

void SceneManager::ReplaceScene(Scene* scene)
{
    delete mCurrentScene;
    mCurrentScene = scene;
}
