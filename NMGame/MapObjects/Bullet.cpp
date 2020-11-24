#include "Bullet.h"
Bullet::Bullet(D3DXVECTOR3 position, int angle)
{
	init(position, angle);
}

Bullet::Bullet()
{

}

Bullet::~Bullet()
{
	delete mAnimation;
}

bool Bullet::init(D3DXVECTOR3 position, int angle)
{
    switch (angle)
    {
    case 0:
        mAnimation = new Animation("Assets/bullet0.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(480);
        this->SetVy(0);
        break;
    case 45:
        mAnimation = new Animation("Assets/bullet45.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(480);
        this->SetVy(-480);
        break;
    case 90:
        mAnimation = new Animation("Assets/bullet90.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(0);
        this->SetVy(-480);
        break;
    case 135:
        mAnimation = new Animation("Assets/bullet135.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(-480);
        this->SetVy(-480);
        break;
    case 180:
        mAnimation = new Animation("Assets/bullet180.png", TotalFrame(), Row(), Column(), SecondPerFrame());
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

void Bullet::SetMission(vector<D3DXVECTOR3> listMission) {

}

void Bullet::OnSetPosition(D3DXVECTOR3 pos)
{
    mAnimation->SetPosition(pos);
}

void Bullet::Update(float dt)
{
    if (mIsValid && mTimeExist >= mTimeExistMaximum)
    {
        mIsValid = false;
    }
    mAnimation->Update(dt);
    mTimeExist += dt;
    Entity::Update(dt);
}

void Bullet::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Bullet::Draw(D3DXVECTOR2 transform)
{
    mAnimation->Draw(transform);
}

const char* Bullet::FileName(char* filePath)
{
    return filePath;
}

int Bullet::TotalFrame()
{
    return 1;
}

int Bullet::Row()
{
    return 1;
}

int Bullet::Column()
{
    return 1;
}

float Bullet::SecondPerFrame()
{
    return 0;
}

void Bullet::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    if ((impactor->Tag == EntityTypes::Player || this->Tag == EntityTypes::Bullets) && impactor->Tag != EntityTypes::Thorns)
    {
        mIsValid = false;
    }
    else
    {
        switch (side)
        {
        case Entity::Left:
            break;

        case Entity::Right:
            break;
        case Entity::Top:
            break;

        case Entity::Bottom:
        case Entity::BottomRight:
        case Entity::BottomLeft:
            if (Tag == EntityTypes::BulletSkulls)
            {
                if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
                {
                    this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
                    this->SetVy(0);
                    this->SetVx(180);
                }
                return;
            }

        default:
            break;
        }
    }
}

RECT Bullet::GetBound()
{
    RECT rect;
    rect.left = this->posX - GetWidth() / 2;
    rect.right = rect.left + GetWidth();
    rect.top = this->posY - GetHeight() / 2;
    rect.bottom = rect.top + GetHeight();
    return rect;
}