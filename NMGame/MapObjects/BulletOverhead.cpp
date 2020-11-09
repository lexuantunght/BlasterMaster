#include "BulletOverhead.h"

BulletOverhead::BulletOverhead(D3DXVECTOR3 position, int angle)
{
	init(position, angle);
}

BulletOverhead::~BulletOverhead()
{
	delete mAnimation;
}

bool BulletOverhead::init(D3DXVECTOR3 position, int angle)
{
    switch (angle)
    {
    case 0:
        mAnimation = new Animation("Assets/bulletOverhead.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(480);
        this->SetVy(0);
        break;
    case 90:
        mAnimation = new Animation("Assets/bulletOverhead90.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(0);
        this->SetVy(-480);
        break;
    case 270:
        mAnimation = new Animation("Assets/bulletOverhead270.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(0);
        this->SetVy(480);
        break;
    case 180:
        mAnimation = new Animation("Assets/bulletOverhead.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        //mAnimation->FlipVertical(true);
        this->SetVx(-480);
        this->SetVy(0);
        break;
    default:
        break;
    }

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::Bullets;

    return true;
}
