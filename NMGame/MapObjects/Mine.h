#pragma once
#include "Enemy.h"
#include "BulletFloater.h"
class Mine : public Enemy
{
public:
	Mine(D3DXVECTOR3 position, int hp, int isContainItem);
	~Mine();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};

