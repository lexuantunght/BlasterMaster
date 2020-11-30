#include "SuperBlock.h"

SuperBlock::SuperBlock()
{

}

SuperBlock::SuperBlock(D3DXVECTOR3 position)
{
	mAnimation = new Animation("Assets/superBlock.png", 1, 1, 1, 0.0f);
	Entity::SetWidth(mAnimation->GetWidth());
	Entity::SetHeight(mAnimation->GetHeight());
	Tag = Entity::EntityTypes::Rocks;
	OnSetPosition(position);
	mDestroyed = false;
}

SuperBlock::~SuperBlock()
{
	delete mAnimation;
}

void SuperBlock::OnSetPosition(D3DXVECTOR3 pos)
{
	mAnimation->SetPosition(pos);
	this->posX = pos.x;
	this->posY = pos.y;
}

void SuperBlock::Update(float dt)
{

}

void SuperBlock::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
	if (impactor->Tag == EntityTypes::Bullets)
	{
		mDestroyed = true;
	}
}

void SuperBlock::Draw()
{
	mAnimation->Draw();
}

void SuperBlock::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}