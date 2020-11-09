#pragma once
#include "Enemy.h"
class Cannon : public Enemy
{
public:
	Cannon(D3DXVECTOR3 position, int hp, int isContainItem);
	~Cannon();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
	float SecondPerFrame();
};

