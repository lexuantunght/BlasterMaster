#include "Teleporter.h"
#include <time.h>
Teleporter::Teleporter(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Teleporter::~Teleporter()
{
    delete mAnimation;
}
bool Teleporter::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    widthBottom = 0;
    vx = 0;
    vy = 0;
    mTimeMove = 2.0f;
    mCurrTime = 0;
    type = EnemyType::teleporter;
    Tag = EntityTypes::Enemy;

    SetPosition(position);
    root = position;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}

void Teleporter::Update(float dt)
{
    if (vx < 0)
        mAnimation->FlipVertical(true);
    else mAnimation->FlipVertical(false);
    mAnimation->SetPosition(this->GetPosition());
    mAnimation->Update(dt);
    for (size_t i = 0; i < mBullets.size(); i++)
    {
        if (mBullets[i] && mBullets[i]->mIsValid)
        {
            mBullets[i]->Update(dt);
        }
        else
        {
            delete mBullets[i];
            mBullets.erase(mBullets.begin() + i);
        }
    }
    Entity::Update(dt);

    mCurrTime += dt;
    if (mCurrTime >= mTimeMove)
    {
        srand(time(NULL));
        int x = rand();
        int y = rand();
        this->AddPosition(pow(-1, x) * 40, pow(-1, y) * 40);
        if (this->GetPosition().x >= root.x + 50)
            this->AddPosition(-40, 0);
        if (this->GetPosition().x <= root.x - 50)
            this->AddPosition(40, 0);
        if (this->GetPosition().y >= root.y + 50)
            this->AddPosition(0, -40);
        if (this->GetPosition().y <= root.y - 50)
            this->AddPosition(0, 40);
        mCurrTime = 0;
    }
}

const char* Teleporter::FileName()
{
    return "Assets/teleporter.png";
}

int Teleporter::TotalFrame()
{
    return 2;
}

int Teleporter::Column()
{
    return 2;
}

float Teleporter::SecondPerFrame()
{
    return 1.0f;
}
