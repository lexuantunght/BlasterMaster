#pragma once
#include "Bullet.h"
class BulletFloater : public Bullet
{
public:
	BulletFloater(D3DXVECTOR3 position);
	~BulletFloater();
private:
	bool init(D3DXVECTOR3 position);
};

