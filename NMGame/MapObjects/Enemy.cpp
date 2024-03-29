#include "Enemy.h"
Enemy::Enemy()
{

}

Enemy::Enemy(D3DXVECTOR3 position, int hp)
{
    init(position, hp);
}

Enemy::~Enemy()
{
    delete mAnimation;
}

bool Enemy::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());
    mHp = hp;
    mIsActive = false;
    mIsContainItem = 0;

    OnSetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}

void Enemy::OnSetPosition(D3DXVECTOR3 pos)
{
    mAnimation->SetPosition(pos);
}

void Enemy::Update(float dt)
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
}

void Enemy::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, transform, angle, rotationCenter, colorKey);
    // vien dan
    for (int i = 0; i < mBullets.size(); i++)
    {
        mBullets[i]->Draw(mBullets[i]->GetPosition());
    }
}

void Enemy::Draw(D3DXVECTOR2 transform)
{
    mAnimation->Draw(D3DXVECTOR3(posX, posY, 0), RECT(), D3DXVECTOR2(), transform);
    for (int i = 0; i < mBullets.size(); i++)
    {
        mBullets[i]->Draw(mBullets[i]->GetPosition(), RECT(), D3DXVECTOR2(), transform);
    }
}

const char* Enemy::FileName()
{
    return "Assets/enemy1.png";
}

int Enemy::TotalFrame()
{
    return 2;
}

int Enemy::Row()
{
    return 1;
}

int Enemy::Column()
{
    return 2;
}

float Enemy::SecondPerFrame()
{
    return 0.25f;
}

RECT Enemy::GetBound()
{
    RECT rect;
    rect.left = this->posX - mAnimation->GetWidth() / 2;
    rect.right = rect.left + mAnimation->GetWidth();
    rect.top = this->posY - mAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mAnimation->GetHeight();
    return rect;
}

int Enemy::GetHP()
{
    return mHp;
}

void Enemy::OnNoCollisionWithBottom()
{
    if (mIsActive)
    {
        this->SetVy(180);
        this->SetVx(0);   
    }
}

void Enemy::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    if (impactor->Tag == EntityTypes::Bullets)
    {
        mHp--;
    }
    else
    {
        switch (side)
        {
        case Entity::Left:
            if (impactor->Tag == EntityTypes::Player)
                this->AddPosition(10, 0);
            else
            {
                this->AddPosition(1, 0);
                this->SetVx(-this->GetVx());
            }
            break;

        case Entity::Right:
            if (impactor->Tag == EntityTypes::Player)
                this->AddPosition(-10, 0);
            else
            {
                this->AddPosition(-1, 0);
                this->SetVx(-this->GetVx());
            }
            break;

        case Entity::Top:
            if (type == EnemyType::floater) this->SetVy(40);
            break;

        case Entity::Bottom:
        case Entity::BottomRight:
        case Entity::BottomLeft:
            if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
            {
                this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
                this->SetVy(0);
                if (type == EnemyType::floater) this->SetVy(-40);
                if (type == EnemyType::jumper) this->SetVy(-120);
            }
            return;

        default:
            break;
        }
    }
}