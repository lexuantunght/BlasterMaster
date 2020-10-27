#include "Jumper.h"
Jumper::Jumper(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Jumper::~Jumper()
{
    delete mAnimation;
}
bool Jumper::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::jumper;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Jumper::FileName()
{
    return "Assets/jumper.png";
}

int Jumper::TotalFrame()
{
    return 3;
}

int Jumper::Column()
{
    return 3;
}