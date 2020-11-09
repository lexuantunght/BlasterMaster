#pragma once
#include <math.h>
#include <vector>
#include <d3d9.h>
#include <d3dx9.h>

#include "../Scene.h"
#include "FirstScene.h"
#include "../Sprite.h"
#include "../Animation.h"
#include "../Player.h"
#include "../Map.h"
#include "../Camera.h"

class Map2Scene : public FirstScene
{
public:
    Map2Scene();
    ~Map2Scene();
    void checkCollision();
    void LoadContent();
    void Update(float dt);
};

