#include "Rock.h"

Rock::Rock()
{

}

Rock::Rock(D3DXVECTOR3 position, int itemCode)
{
	mAnimation = new Animation("Assets/rock.png", 1, 1, 1, 0.0f);
	if (itemCode != 0)
	{
		mItem = new ItemCollection(position, itemCode);
	}
	else mItem = nullptr;
	Entity::SetWidth(mAnimation->GetWidth());
	Entity::SetHeight(mAnimation->GetHeight());
	Tag = Entity::EntityTypes::Rocks;
	OnSetPosition(position);
	mDestroyed = false;
}

Rock::~Rock()
{
	delete mAnimation;
}

void Rock::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
	this->posX = pos.x;
	this->posY = pos.y;
}

void Rock::Update(float dt)
{

}

void Rock::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == EntityTypes::Bullets)
	{
		mDestroyed = true;
	}
}

void Rock::Draw()
{
	mAnimation->Draw();
}

void Rock::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}
