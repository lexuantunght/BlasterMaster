#pragma once
#include "Bullet.h"
class BulletSkull : public Bullet
{
public:
	BulletSkull(D3DXVECTOR3 position);
	~BulletSkull();
private:
	bool init(D3DXVECTOR3 position);
};