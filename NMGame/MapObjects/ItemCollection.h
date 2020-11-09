#pragma once
#include "../Sprite.h"
class ItemCollection
{
public:
	ItemCollection(D3DXVECTOR3 position, int kind);
	~ItemCollection();
	int kindItem;
	Sprite* mSprite;
};

