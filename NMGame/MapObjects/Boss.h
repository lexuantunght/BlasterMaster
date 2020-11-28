#pragma once
#include "Enemy.h"
#include "BossHand.h"

class Boss : public Enemy
{
public:
	Boss(D3DXVECTOR3 position, int hp, int isContainItem);
	~Boss();
	void Update(float dt);
	void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	void Draw(D3DXVECTOR2 transform);
	void MoveHandLeft();
	void MoveHandRight();
	vector<BossHand*> GetBossHandLeft();
	vector<BossHand*> GetBossHandRight();
private:
	bool init(D3DXVECTOR3 position, int hp);
	const char* FileName();
	int TotalFrame();
	int Column();
	vector<BossHand*> leftHands;
	vector<BossHand*> rightHands;
	float mPrepareTime;
	float mMoveHandTime;
	int mMoveHandStep;
	float mMoveHandRightTime;
	int mMoveHandRightStep;
	float mTimeBullet;
};
