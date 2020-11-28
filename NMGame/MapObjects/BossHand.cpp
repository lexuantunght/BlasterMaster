#include "BossHand.h"
BossHand::BossHand(const char* filePath, D3DXVECTOR3 position)
{
    mSprite = new Sprite(filePath);
    SetPosition(position);
    mSprite->SetPosition(position);
    vx = 0;
    vy = 0;
    Entity::SetWidth(mSprite->GetWidth());
    Entity::SetHeight(mSprite->GetHeight());
    Tag = EntityTypes::BossHands;
}
BossHand::~BossHand()
{
    delete mSprite;
}
void BossHand::Draw(D3DXVECTOR2 transform)
{
    mSprite->Draw(mSprite->GetPosition(), RECT(), D3DXVECTOR2(), transform);
}
void BossHand::OnSetPosition(D3DXVECTOR3 pos)
{
    mSprite->SetPosition(pos);
}
void BossHand::Update(float dt)
{
    OnSetPosition(GetPosition());
    Entity::Update(dt);
}