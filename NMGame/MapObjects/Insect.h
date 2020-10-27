#pragma once
#include "Enemy.h"
class Insect : public Enemy
{
public:
	Insect(D3DXVECTOR3 position, int hp, int isContainItem);
	~Insect();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};

