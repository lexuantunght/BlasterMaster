#pragma once
#include "Enemy.h"
class Jumper : public Enemy
{
public:
	Jumper(D3DXVECTOR3 position, int hp, int isContainItem);
	~Jumper();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};

