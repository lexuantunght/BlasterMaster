#include "Worm.h"
Worm::Worm(D3DXVECTOR3 position, int hp, int isContainItem)
{
	init(position, hp);
    mIsContainItem = isContainItem;
}
Worm::~Worm()
{
	delete mAnimation;
}
bool Worm::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    type = EnemyType::worm;
    Tag = EntityTypes::Enemy;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}
const char* Worm::FileName()
{
	return "Assets/worm.png";
}

int Worm::TotalFrame()
{
	return 2;
}

int Worm::Column()
{
	return 2;
}
