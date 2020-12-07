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
#include "../MapObjects/Mine.h"
#include "../MapObjects/Enemy.h"
#include "../Views/Menu.h"
#include "../MapObjects/SuperBlock.h"

class FirstScene : public Scene
{
public:
    FirstScene();
    FirstScene(D3DXVECTOR3 lastPos);
    FirstScene(D3DXVECTOR3 newPos, bool currReverse, bool superBullet);
    ~FirstScene();

    void Update(float dt);
    void LoadContent();
    void Draw();

    void OnKeyDown(int keyCode);
    void OnKeyUp(int keyCode);
    void OnMouseDown(float x, float y);

    void LoadEnemies(const char* path);
    void LoadMapBound(const char* path);
    void LoadSuperBlocks(const char* path);

    static vector<Enemy*> mEnemies;
protected:
    void checkCollision();
    void CheckCameraAndWorldMap();
    void InitForEnemies(float dt);
    void PassGateRight();
    void PassGateLeft();
    bool mIsPassGateRight = false;
    bool mIsPassGateLeft = false;
    bool mIsShowMenu = false;
    bool mIsSoundMine = false;
    bool mIsPlaySound = false;

    Player* mPlayer;
    Map* mMap;
    Camera* mCamera;
    RECT mCurrentMapBound;
    int mCurrentMapIndex;
    RECT* mListMapBound;
    vector<Sprite*> mPowerCollections;
    vector<SuperBlock*> mSuperBlocks;
    Menu* menu;

    float mTimeCounter;

    std::map<int, bool> keys;
};

