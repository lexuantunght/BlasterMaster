#include "BulletEyeball.h"
BulletEyeball::BulletEyeball(D3DXVECTOR3 position)
{
    init(position);
}

BulletEyeball::~BulletEyeball()
{
    delete mAnimation;
}

bool BulletEyeball::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation("Assets/bullet_eyeball.png", TotalFrame(), Row(), Column(), SecondPerFrame());
    this->SetVx(0);
    this->SetVy(0);

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    mTimeExistMaximum = 3;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::BulletEyeballs;

    return true;
}