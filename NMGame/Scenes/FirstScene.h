#pragma once
#include <math.h>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

#include "../Scene.h"
#include "../Sprite.h"
#include "../Animation.h"
#include "../Player.h"
#include "../Map.h"
#include "../Camera.h"
#include "../MapObjects/Worm.h"
#include "../MapObjects/Dome.h"
#include "../MapObjects/Floater.h"
#include "../MapObjects/Jumper.h"
#include "../MapObjects/Insect.h"
#include "../MapObjects/Skull.h"
#include "../MapObjects/Orb.h"
#include "../MapObjects/Enemy.h"

class FirstScene : public Scene
{
public:
    FirstScene();

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);

    void LoadEnemies(const char* path);
    void LoadMapBound(const char* path);
protected:
    void checkCollision();
    void CheckCameraAndWorldMap();
    void PassGateRight();
    void PassGateLeft();
    bool mIsPassGateRight = false;
    bool mIsPassGateLeft = false;

    Player* mPlayer;
    Map* mMap;
    Camera* mCamera;
    RECT mCurrentMapBound;
    RECT* mListMapBound;
    vector<Enemy*> mEnemies;
    vector<Sprite*> mPowerCollections;

    float mTimeCounter;

    std::map<int, bool> keys;
};

