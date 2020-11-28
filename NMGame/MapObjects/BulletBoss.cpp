#include "BulletBoss.h"

BulletBoss::BulletBoss(D3DXVECTOR3 position)
{
    init(position);
}

BulletBoss::~BulletBoss()
{
    delete mAnimation;
}

bool BulletBoss::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation("Assets/Boss/bossBullet.png", TotalFrame(), Row(), Column(), SecondPerFrame());
    this->SetVx(0);
    this->SetVy(80);

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    mTimeExistMaximum = 5;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::BulletBosses;

    return true;
}