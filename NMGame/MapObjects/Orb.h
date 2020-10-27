#pragma once
#include "Enemy.h"
class Orb : public Enemy
{
public:
	Orb(D3DXVECTOR3 position, int hp, int isContainItem);
	~Orb();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};

