#include "Mine.h"
Mine::Mine(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Mine::~Mine()
{
    delete mAnimation;
}
bool Mine::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::mine;
    Tag = EntityTypes::Enemy;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Mine::FileName()
{
    return "Assets/mine.png";
}

int Mine::TotalFrame()
{
    return 2;
}

int Mine::Column()
{
    return 2;
}