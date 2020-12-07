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
#include "../MapObjects/Enemy.h"
#include "../MapObjects/ItemCollection.h"
#include "../MapObjects/Rock.h"
class ThirdScene : public Scene
{
public:
    ThirdScene();
    ThirdScene(D3DXVECTOR3 lastPos, D3DXVECTOR3 oldPos, bool currReverse);
    ~ThirdScene();
    ThirdScene(D3DXVECTOR3 oldPos, bool currReverse);

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);

    void LoadEnemies(const char* path);
    void LoadMapBound(const char* path);
    void LoadRocks(const char* path);
protected:
    void checkCollision();
    void CheckCameraAndWorldMap();
    void InitForEnemies(float dt);
    void PassGateRight();
    void PassGateLeft();
    void PassGateTop();
    void PassGateBottom();
    bool mIsPassGateRight = false;
    bool mIsPassGateLeft = false;
    bool mIsPassGateTop = false;
    bool mIsPassGateBottom = false;

    bool currReverse;
    D3DXVECTOR3 oldPos;

    Player* mPlayer;
    Map* mMap;
    Camera* mCamera;
    RECT mCurrentMapBound;
    RECT* mListMapBound;
    vector<Enemy*> mEnemies;
    vector<Rock*> mRocks;
    vector<ItemCollection*> mItemCollections;

    Animation* bossStage;
    Sprite* bossBackground;
    bool mIsBossStage;
    bool mIsLoadedBossStage;
    bool mIsKilledBoss;
    bool getMachine;
    float mCountPreBoss;

    float mTimeCounter;

    std::map<int, bool> keys;
};

