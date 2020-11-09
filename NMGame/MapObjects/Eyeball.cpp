#include "Eyeball.h"
Eyeball::Eyeball(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Eyeball::~Eyeball()
{
    delete mAnimation;
}
bool Eyeball::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::eyeball;
    Tag = EntityTypes::Enemy;
    vx = 80;
    vy = 80;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}

void Eyeball::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    if (impactor->Tag == EntityTypes::Bullets)
    {
        mHp--;
    }
    else
    {
        switch (side)
        {
        case Entity::Left:
            if (impactor->Tag == EntityTypes::Player)
            {

            }
            else if (impactor->Tag != EntityTypes::Ladder)
            {
                this->AddPosition(1, 0);
                this->SetVx(-this->GetVx());
            }
            break;

        case Entity::Right:
            if (impactor->Tag == EntityTypes::Player)
            {

            }
            else if (impactor->Tag != EntityTypes::Ladder)
            {
                this->AddPosition(-1, 0);
                this->SetVx(-this->GetVx());
            }
            break;

        case Entity::Top:
            this->SetVy(80);
            break;

        case Entity::Bottom:
        case Entity::BottomRight:
        case Entity::BottomLeft:
            if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
            {
                this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
                this->SetVy(-80);
            }
            break;

        default:
            break;
        }
    }
}

const char* Eyeball::FileName()
{
    return "Assets/eyeball.png";
}

int Eyeball::TotalFrame()
{
    return 3;
}

int Eyeball::Column()
{
    return 3;
}