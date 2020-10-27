#pragma once
#include "Enemy.h"
class Worm : public Enemy
{
public:
	Worm(D3DXVECTOR3 position, int hp, int isContainItem);
	~Worm();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};

