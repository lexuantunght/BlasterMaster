#pragma once
#include "Enemy.h"
#include "BulletFloater.h"
class Floater : public Enemy
{
public:
	Floater(D3DXVECTOR3 position, int hp, int isContainItem);
	~Floater();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};