#pragma once
#include "Bullet.h"
class ThunderBullet : public Bullet
{
public:
	ThunderBullet(D3DXVECTOR3 position);
	~ThunderBullet();
	void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
};

