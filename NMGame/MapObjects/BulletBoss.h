#pragma once
#include "Bullet.h"
class BulletBoss : public Bullet
{
public:
	BulletBoss(D3DXVECTOR3 position);
	~BulletBoss();
private:
	bool init(D3DXVECTOR3 position);
};

