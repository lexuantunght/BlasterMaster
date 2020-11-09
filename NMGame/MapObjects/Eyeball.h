#pragma once
#include "Enemy.h"
#include "BulletEyeball.h"
class Eyeball : public Enemy
{
public:
	Eyeball(D3DXVECTOR3 position, int hp, int isContainItem);
	~Eyeball();
	void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
};

