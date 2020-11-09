#include "Cannon.h"
Cannon::Cannon(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Cannon::~Cannon()
{
    delete mAnimation;
}
bool Cannon::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    vx = 0;
    vy = 0;
    type = EnemyType::cannon;
    Tag = EntityTypes::Enemy;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Cannon::FileName()
{
    return "Assets/cannon.png";
}

int Cannon::TotalFrame()
{
    return 2;
}

int Cannon::Column()
{
    return 2;
}

float Cannon::SecondPerFrame()
{
    return 0.5f;
}