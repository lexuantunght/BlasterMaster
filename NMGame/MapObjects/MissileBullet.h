#pragma once
#include "Bullet.h"
class MissileBullet : public Bullet
{
public:
	MissileBullet(D3DXVECTOR3 position, int angle);
	~MissileBullet();
	void Update(float dt);
	void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	void SetMission(vector<D3DXVECTOR3> listMission);
private:
	int FindIndexMinDistance();
	void GotoEnemy();
	vector<D3DXVECTOR3> listMission;
};

