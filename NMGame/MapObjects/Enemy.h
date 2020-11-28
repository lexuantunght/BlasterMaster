#pragma once
#include "../Entity.h"
#include "../Animation.h"
#include "../Collision.h"
#include "Bullet.h"
#include "BossHand.h"
class Enemy : public Entity
{
public:
	Enemy();
	Enemy(D3DXVECTOR3 position, int hp);
	~Enemy();
	enum EnemyType
	{
		worm, dome, jumper, floater, insect, orb, skull, mine, teleporter, cannon, eyeball, boss
	};
	virtual void Update(float dt);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	virtual void Draw(D3DXVECTOR2 transform);

	virtual void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

	virtual vector<BossHand*> GetBossHandLeft();
	virtual vector<BossHand*> GetBossHandRight();

	void OnNoCollisionWithBottom();
	RECT GetBound();
	int widthBottom;
	int GetHP();
	bool mIsActive;
	EnemyType type;
	vector<Bullet*> mBullets;
	int mIsContainItem;
	bool mIsGoDown;
protected:
	virtual bool init(D3DXVECTOR3 position, int hp);
	void OnSetPosition(D3DXVECTOR3 pos);
	virtual const char* FileName();
	virtual int TotalFrame();
	int Row();
	virtual int Column();
	virtual float SecondPerFrame();
	Animation* mAnimation;
	int mHp;
};

