#pragma once
#include "Bullet.h"
class BulletOverhead : public Bullet
{
public:
	BulletOverhead(D3DXVECTOR3 position, int angle);
	~BulletOverhead();
private:
	bool init(D3DXVECTOR3 position, int angle);
};

