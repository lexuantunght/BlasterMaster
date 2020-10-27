#include "Orb.h"
Orb::Orb(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Orb::~Orb()
{
    delete mAnimation;
}
bool Orb::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::orb;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Orb::FileName()
{
    return "Assets/orb.png";
}

int Orb::TotalFrame()
{
    return 2;
}

int Orb::Column()
{
    return 2;
}