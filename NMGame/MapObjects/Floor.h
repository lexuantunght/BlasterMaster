#pragma once
#include "MapObject.h"
#include "../Entity.h"
#include "../Sprite.h"

class Floor : public Entity
{
public:
	Floor(D3DXVECTOR3 position);
	~Floor();
	void Update(float dt);
	void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
	void Draw(D3DXVECTOR2 transform);
private:
	bool init(D3DXVECTOR3 position);
	void OnSetPosition(D3DXVECTOR3 pos);
	const char* FileName();
	Sprite* mSprite;
};

