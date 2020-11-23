#pragma once
#include "../Entity.h"
#include "../Animation.h"
class Bullet : public Entity
{
public:
	Bullet(D3DXVECTOR3 position, int angle);
	Bullet();
	~Bullet();
	virtual void Update(float dt);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(D3DXVECTOR2 transform);
	virtual void SetMission(vector<D3DXVECTOR3> listMission);
	virtual void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);
	RECT GetBound();
	bool mIsValid;
private:
	bool init(D3DXVECTOR3 position, int angle);
protected:
	void OnSetPosition(D3DXVECTOR3 pos);
	const char* FileName(char* filePath);
	int TotalFrame();
	int Row();
	int Column();
	float SecondPerFrame();
	float mTimeExist;
	float mTimeExistMaximum = 0.5f;
	D3DXVECTOR3 mStartedPosition;
	Animation* mAnimation;
};