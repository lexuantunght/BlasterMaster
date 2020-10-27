#include "Dome.h"
Dome::Dome(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Dome::~Dome()
{
    delete mAnimation;
}
bool Dome::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::dome;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Dome::FileName()
{
    return "Assets/dome.png";
}

int Dome::TotalFrame()
{
    return 2;
}

int Dome::Column()
{
    return 2;
}