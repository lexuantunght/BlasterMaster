#pragma once
#include "../Scene.h"
#include "../Sprite.h"
#include "../Animation.h"
#include "../Player.h"
#include "../Map.h"
#include "../Camera.h"
#include "FirstScene.h"

class Map1Scene : public FirstScene
{
public:
	Map1Scene();
	void LoadContent();
	void checkCollision();
	void Update(float dt);
	bool mIsCanUpdate = true;
	~Map1Scene();
};

