#include "ThirdScene.h"
#include "../PlayerOverhead.h"
#include <string>
#include <fstream>
ThirdScene::ThirdScene()
{
	LoadContent();
}

ThirdScene::ThirdScene(D3DXVECTOR3 oldPos, bool currReverse)
{
	this->currReverse = currReverse;
	this->oldPos = oldPos;
	LoadContent();
}

ThirdScene::~ThirdScene()
{
    delete mPlayer;
    delete mMap;
}

void ThirdScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x1E1E1E;
    isReplace = false;

    mMap = new Map("Assets/overworld2.tmx");
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - GameGlobal::GetHeight() / 4);
    //mCamera->SetPosition(3584, 702);
    mMap->SetCamera(mCamera);

    LoadEnemies("Assets/enemies_overworld2.txt");

    //get bound submap
    mListMapBound = new RECT[21];
    LoadMapBound("Assets/map_bounds_overworld2.txt");
    mCurrentMapBound = mListMapBound[0];

    mPlayer = new PlayerOverhead();
    mPlayer->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - GameGlobal::GetHeight() / 4);
    //mPlayer->SetPosition(3584, 702);
    mPlayer->SetCamera(mCamera);
}