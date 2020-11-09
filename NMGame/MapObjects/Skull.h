#pragma once
#include "Enemy.h"
#include "BulletSkull.h"
class Skull : public Enemy
{
public:
	Skull(D3DXVECTOR3 position, int hp, int isContainItem);
	~Skull();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};

