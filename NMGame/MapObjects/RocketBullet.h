#pragma once
#include "Bullet.h"
class RocketBullet : public Bullet
{
public:
	RocketBullet(D3DXVECTOR3 position, int angle, int id);
	~RocketBullet();
	void Update(float dt);
	void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
private:
	int id;
};

