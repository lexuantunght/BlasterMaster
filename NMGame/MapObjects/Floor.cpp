#include "Floor.h"
#include "../GameGlobal.h"

Floor::Floor(D3DXVECTOR3 position)
{
	init(position);
}
Floor::~Floor()
{

}
bool Floor::init(D3DXVECTOR3 position)
{
	mSprite = new Sprite(FileName());
	Entity::SetPosition(position);
	Entity::SetWidth(mSprite->GetWidth());
	Entity::SetHeight(mSprite->GetHeight());
	return true;
}

const char* Floor::FileName()
{
	return "Assets/normalbrick.png";
}

void Floor::OnSetPosition(D3DXVECTOR3 pos)
{
	mSprite->SetPosition(pos);
}

void Floor::Update(float dt)
{
	
}

void Floor::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
	mSprite->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Floor::Draw(D3DXVECTOR2 transform)
{
	mSprite->Draw(D3DXVECTOR3(transform));
}