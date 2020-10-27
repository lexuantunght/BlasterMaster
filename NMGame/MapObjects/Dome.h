#pragma once
#include "Enemy.h"
class Dome : public Enemy
{
public:
	Dome(D3DXVECTOR3 position, int hp, int isContainItem);
	~Dome();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};

