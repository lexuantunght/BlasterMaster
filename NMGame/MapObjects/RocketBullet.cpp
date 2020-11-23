#include "RocketBullet.h"

RocketBullet::RocketBullet(D3DXVECTOR3 position, int angle, int id)
{
    if (angle == 0)
    {
        mAnimation = new Animation("Assets/rocketBullet0.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(480);
    }
    else
    {
        mAnimation = new Animation("Assets/rocketBullet180.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(-480);
    }

    mTimeExistMaximum = 0.5f;
    this->id = id;
    if (id == 1)
        this->SetVy(-280);
    else if (id == 2)
        this->SetVy(0);
    else this->SetVy(280);

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::Bullets;
}

RocketBullet::~RocketBullet()
{

}

void RocketBullet::Update(float dt)
{
    if (mTimeExist >= 0.15f)
        this->SetVy(0);
    if (mIsValid && mTimeExist >= mTimeExistMaximum)
    {
        mIsValid = false;
    }
    mAnimation->Update(dt);
    mTimeExist += dt;
    Entity::Update(dt);
}

void RocketBullet::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

}