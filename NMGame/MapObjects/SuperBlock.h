#pragma once
#include "../Entity.h"
#include "../Animation.h"
class SuperBlock : public Entity
{
public:
	SuperBlock();
	SuperBlock(D3DXVECTOR3 position);
	~SuperBlock();
	void Update(float dt);
	void Draw();
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	bool mDestroyed;
private:
	Animation* mAnimation;
	void OnSetPosition(D3DXVECTOR3 pos);
};

