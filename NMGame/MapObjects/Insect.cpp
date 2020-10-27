#include "Insect.h"
Insect::Insect(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Insect::~Insect()
{
    delete mAnimation;
}
bool Insect::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::insect;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Insect::FileName()
{
    return "Assets/insect.png";
}

int Insect::TotalFrame()
{
    return 2;
}

int Insect::Column()
{
    return 2;
}