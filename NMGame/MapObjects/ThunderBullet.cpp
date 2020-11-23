#include "ThunderBullet.h"

ThunderBullet::ThunderBullet(D3DXVECTOR3 position)
{
    mAnimation = new Animation("Assets/thunderBullet.png", TotalFrame(), Row(), Column(), SecondPerFrame());
    this->SetVx(0);
    this->SetVy(0);

    mTimeExistMaximum = 0.1f;

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::Bullets;
}

ThunderBullet::~ThunderBullet()
{

}

void ThunderBullet::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

}