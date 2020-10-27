#include "Floater.h"
Floater::Floater(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Floater::~Floater()
{
    delete mAnimation;
}
bool Floater::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::floater;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Floater::FileName()
{
    return "Assets/floater.png";
}

int Floater::TotalFrame()
{
    return 2;
}

int Floater::Column()
{
    return 2;
}