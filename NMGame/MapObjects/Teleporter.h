#pragma once
#include "Enemy.h"
class Teleporter : public Enemy
{
public:
	Teleporter(D3DXVECTOR3 position, int hp, int isContainItem);
	~Teleporter();
	void Update(float dt);
	float mTimeMove;
	float mCurrTime;
	D3DXVECTOR3 root;
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
	float SecondPerFrame();
};

