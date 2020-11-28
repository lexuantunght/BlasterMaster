#pragma once
#include "../Entity.h"
#include "../Sprite.h"
class BossHand : public Entity
{
public:
	BossHand(const char* filePath, D3DXVECTOR3 position);
	~BossHand();
	void Draw(D3DXVECTOR2 transform);
	void Update(float dt);
	void OnSetPosition(D3DXVECTOR3 pos);
private:
	Sprite* mSprite;
};