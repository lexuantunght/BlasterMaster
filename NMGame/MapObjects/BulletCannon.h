#pragma once
#include "Bullet.h"
class BulletCannon : public Bullet
{
public:
	BulletCannon(D3DXVECTOR3 position);
	~BulletCannon();
private:
	bool init(D3DXVECTOR3 position);
};

