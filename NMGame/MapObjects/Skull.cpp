#include "Skull.h"
Skull::Skull(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Skull::~Skull()
{
    delete mAnimation;
}
bool Skull::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::skull;
    vx = -180;
    vy = 0;
    Tag = EntityTypes::Enemy;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Skull::FileName()
{
    return "Assets/skull.png";
}

int Skull::TotalFrame()
{
    return 2;
}

int Skull::Column()
{
    return 2;
}