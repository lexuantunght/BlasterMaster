#include "BulletFloater.h"
BulletFloater::BulletFloater(D3DXVECTOR3 position)
{
    init(position);
}

BulletFloater::~BulletFloater()
{
    delete mAnimation;
}

bool BulletFloater::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation("Assets/bullet_floater.png", TotalFrame(), Row(), Column(), SecondPerFrame());
    this->SetVx(0);
    this->SetVy(0);

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    mTimeExistMaximum = 3;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::BulletFloaters;

    return true;
}