#include "BulletCannon.h"
BulletCannon::BulletCannon(D3DXVECTOR3 position)
{
    init(position);
}

BulletCannon::~BulletCannon()
{
    delete mAnimation;
}

bool BulletCannon::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation("Assets/bullet_cannon.png", TotalFrame(), Row(), Column(), SecondPerFrame());
    this->SetVx(0);
    this->SetVy(0);

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    mTimeExistMaximum = 10;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::BulletCannons;

    return true;
}