#include "ItemCollection.h"
ItemCollection::ItemCollection(D3DXVECTOR3 position, int kind)
{
	if (kind == 1) mSprite = new Sprite("Assets/powerCollection.png");
	else if (kind == 2) mSprite = new Sprite("Assets/gunCollection.png");
	else if (kind == 3) mSprite = new Sprite("Assets/hoverCollection.png");
	else if (kind == 4) mSprite = new Sprite("Assets/thunderBreak.png");
	else if (kind == 5) mSprite = new Sprite("Assets/homingMissile.png");

	kindItem = kind;
	mSprite->SetPosition(position);
}

ItemCollection::~ItemCollection()
{
	delete mSprite;
}