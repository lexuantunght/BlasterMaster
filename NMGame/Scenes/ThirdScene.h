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
#include "SecondScene.h"
#include "../MapObjects/Enemy.h"
#include "../MapObjects/ItemCollection.h"
class ThirdScene : public SecondScene
{
public:
    ThirdScene();
    ThirdScene(D3DXVECTOR3 oldPos, bool currReverse);

    void LoadContent();
};

