#pragma once
#include <d3dx9.h>
#include <d3d9.h>
#include <vector>

#include "Sprite.h"
#include "MapReader/Tmx.h.in"
#include "GameGlobal.h"
#include "Camera.h"
#include "MapObjects/Floor.h"
#include "QuadTree.h"
#include "Collision.h"
#include "MapObjects/Bee.h"

class Map
{
public:
    Map(const char* filePath);

    Tmx::Map* GetMap();

    int GetWidth();
    int GetHeight();
    int GetTileWidth();
    int GetTileHeight();

    void SetCamera(Camera* camera);

    void Update(float dt);

    void Draw();
    void DrawGates();
    std::map<int, Sprite*> getListTileSet();

    bool IsBoundLeft(); //kiem tra luc nay Camera o vi bien ben trai so voi WorldMap
    bool IsBoundRight(); // kiem tra xem co o vi tri bien ben phai worldmap khong
    bool IsBoundTop(); // kiem tra xem co o vi tri bien ben trai worldmap khong
    bool IsBoundBottom(); // kiem tra xem co o vi tri bien ben phai worldmap khong

    RECT GetWorldMapBound();

    QuadTree* GetQuadTree();

    std::vector<Bee*> GetListBees();

    ~Map();

private:
    void LoadMap(const char* filePath);

    bool isContain(RECT rect1, RECT rect2);

    Tmx::Map*                       mMap;
    LPD3DXSPRITE                    mSpriteHandler;
    std::map<int, Sprite*>          mListTileset;
    Camera*                         mCamera;
    QuadTree*                       mQuadTree;
    std::vector<Bee*>               mBees;
};