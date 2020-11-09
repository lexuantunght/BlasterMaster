#pragma once
#include "Bullet.h"
class BulletEyeball : public Bullet
{
public:
	BulletEyeball(D3DXVECTOR3 position);
	~BulletEyeball();
private:
	bool init(D3DXVECTOR3 position);
};

