#include "Boss.h"
#include <time.h>
#include "BulletBoss.h"
#include "../GameSound.h"

Boss::Boss(D3DXVECTOR3 position, int hp, int isContainItem)
{
    init(position, hp);
    mIsContainItem = isContainItem;
}
Boss::~Boss()
{
    delete mAnimation;
}
bool Boss::init(D3DXVECTOR3 position, int hp)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), 0.2f);
    mHp = hp;
    widthBottom = 0;
    mPrepareTime = 0;
    mTimeBullet = 0;
    mMoveHandStep = 0;
    mMoveHandTime = 0;
    mMoveHandRightStep = 4;
    mMoveHandRightTime = 0;
    type = EnemyType::boss;
    Tag = EntityTypes::Enemy;
    vx = 40;
    vy = 40;

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    for (int i = 0; i < 4; i++)
    {
        leftHands.push_back(new BossHand("Assets/Boss/bossHandLeft1.png", D3DXVECTOR3(this->GetPosition().x + 40 + 32 * i, this->GetPosition().y + 40 * i, 0)));
        rightHands.push_back(new BossHand("Assets/Boss/bossHandRight1.png", D3DXVECTOR3(this->GetPosition().x - 40 - 32 * i, this->GetPosition().y + 40 * i, 0)));
    }
    leftHands.push_back(new BossHand("Assets/Boss/bossHandLeft2.png", D3DXVECTOR3(this->GetPosition().x + 40 + 128, this->GetPosition().y + 160, 0)));
    rightHands.push_back(new BossHand("Assets/Boss/bossHandRight2.png", D3DXVECTOR3(this->GetPosition().x - 40 - 128, this->GetPosition().y + 160, 0)));

    return true;
}

void Boss::Update(float dt)
{
    if (mPrepareTime >= 3)
    {
        if (mAnimation->GetPosition().y >= 1184)
            this->SetVy(-40);
        mAnimation->SetPosition(this->GetPosition());
        mAnimation->Update(dt);
        //move hand
        MoveHandLeft();
        MoveHandRight();
        mMoveHandTime += dt;
        mMoveHandRightTime += dt;
        //set v hand
        for (int i = 0; i < 5; i++)
        {
            leftHands.at(i)->Update(dt);
            rightHands.at(i)->Update(dt);
        }
        //bullet
        if (mTimeBullet >= 0.5f)
        {
            if (mBullets.size() < 4)
                mBullets.push_back(new BulletBoss(this->GetPosition()));
            mTimeBullet = 0;
        }
        else mTimeBullet += dt;
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
    else
    {
        if (mPrepareTime + dt >= 3.0f)
            GameSound::GetInstance()->PlayRepeat("Assets/Sounds/boss.mp3");
        mPrepareTime += dt;
    }
}

void Boss::MoveHandLeft()
{
    if (mMoveHandStep > 5)
        mMoveHandStep = 0;
    switch (mMoveHandStep)
    {
    case 0:
        for (int i = 0; i < 5; i++)
        {
            if (leftHands[i]->GetPosition().x > this->GetPosition().x + 40)
                leftHands[i]->SetVx(-80 * i);
            else leftHands[i]->SetVx(0);
            leftHands[i]->SetVx(leftHands[i]->GetVx() + this->vx);
            leftHands[i]->SetVy(this->vy);
        }
        break;
    case 1:
        for (int i = 0; i < 5; i++)
        {
            if (leftHands[i]->GetPosition().x > this->GetPosition().x + 40 - 10 * i)
            {
                leftHands[i]->SetVx(-80 * i);
            }
            else leftHands[i]->SetVx(0);
            if (leftHands[i]->GetPosition().y > this->GetPosition().y - 40 * i)
                leftHands[i]->SetVy(-80 * i);
            else leftHands[i]->SetVy(0);
            if (leftHands[i]->GetVy() == 0)
            {
                if (leftHands[i]->GetPosition().x < this->GetPosition().x + 40)
                    leftHands[i]->SetVx(80 * i);
                else leftHands[i]->SetVx(0);
            }
            leftHands[i]->SetVy(leftHands[i]->GetVy() + this->vy);
            leftHands[i]->SetVx(leftHands[i]->GetVx() + this->vx);
        }
        break;
    case 2:
        for (int i = 0; i < 5; i++)
        {
            if (leftHands[i]->GetPosition().x < this->GetPosition().x + 40 + 10 * i)
            {
                leftHands[i]->SetVx(80 * i);
            }
            else leftHands[i]->SetVx(0);
            if (leftHands[i]->GetPosition().y < this->GetPosition().y + 40 * i)
                leftHands[i]->SetVy(80 * i);
            else leftHands[i]->SetVy(0);
            if (leftHands[i]->GetVy() == 0)
            {
                if (leftHands[i]->GetPosition().x > this->GetPosition().x + 40)
                    leftHands[i]->SetVx(-80 * i);
                else leftHands[i]->SetVx(0);
            }
            leftHands[i]->SetVy(leftHands[i]->GetVy() + this->vy);
            leftHands[i]->SetVx(leftHands[i]->GetVx() + this->vx);
        }
        break;
    case 3:
        for (int i = 0; i < 5; i++)
        {
            if (leftHands[i]->GetPosition().x < this->GetPosition().x + 40 + 32 * i)
                leftHands[i]->SetVx(80 * i);
            else leftHands[i]->SetVx(0);
            leftHands[i]->SetVx(leftHands[i]->GetVx() + this->vx);
            leftHands[i]->SetVy(this->vy);
        }
        break;
    case 4:
        for (int i = 0; i < 5; i++)
        {
            if (leftHands[i]->GetPosition().y > this->GetPosition().y - 40 * i)
                leftHands[i]->SetVy(-80 * i);
            else leftHands[i]->SetVy(0);
            leftHands[i]->SetVy(leftHands[i]->GetVy() + this->vy);
            leftHands[i]->SetVx(this->vx);
        }
        break;
    default:
        for (int i = 0; i < 5; i++)
        {
            if (leftHands[i]->GetPosition().y < this->GetPosition().y + 40 * i)
                leftHands[i]->SetVy(80 * i);
            else leftHands[i]->SetVy(0);
            leftHands[i]->SetVy(leftHands[i]->GetVy() + this->vy);
            leftHands[i]->SetVx(this->vx);
        }
        break;
    }
    if (mMoveHandTime >= 1.5f && (mMoveHandStep == 1 || mMoveHandStep == 2))
    {
        mMoveHandStep++;
        mMoveHandTime = 0;
    }
    else if (mMoveHandTime >= 0.75f && (mMoveHandStep != 1 && mMoveHandStep != 2))
    {
        mMoveHandStep++;
        mMoveHandTime = 0;
    }
}

void Boss::MoveHandRight()
{
    if (mMoveHandRightStep > 5)
        mMoveHandRightStep = 0;
    switch (mMoveHandRightStep)
    {
    case 0:
        for (int i = 0; i < 5; i++)
        {
            if (rightHands[i]->GetPosition().x < this->GetPosition().x - 40)
                rightHands[i]->SetVx(80 * i);
            else rightHands[i]->SetVx(0);
            rightHands[i]->SetVx(rightHands[i]->GetVx() + this->vx);
            rightHands[i]->SetVy(this->vy);
        }
        break;
    case 1:
        for (int i = 0; i < 5; i++)
        {
            if (rightHands[i]->GetPosition().x < this->GetPosition().x - 40 + 10 * i)
            {
                rightHands[i]->SetVx(80 * i);
            }
            else rightHands[i]->SetVx(0);
            if (rightHands[i]->GetPosition().y > this->GetPosition().y - 40 * i)
                rightHands[i]->SetVy(-80 * i);
            else rightHands[i]->SetVy(0);
            if (rightHands[i]->GetVy() == 0)
            {
                if (rightHands[i]->GetPosition().x > this->GetPosition().x - 40)
                    rightHands[i]->SetVx(-80 * i);
                else rightHands[i]->SetVx(0);
            }
            rightHands[i]->SetVy(rightHands[i]->GetVy() + this->vy);
            rightHands[i]->SetVx(rightHands[i]->GetVx() + this->vx);
        }
        break;
    case 2:
        for (int i = 0; i < 5; i++)
        {
            if (rightHands[i]->GetPosition().x > this->GetPosition().x - 40 - 10 * i)
            {
                rightHands[i]->SetVx(-80 * i);
            }
            else rightHands[i]->SetVx(0);
            if (rightHands[i]->GetPosition().y < this->GetPosition().y + 40 * i)
                rightHands[i]->SetVy(80 * i);
            else rightHands[i]->SetVy(0);
            if (rightHands[i]->GetVy() == 0)
            {
                if (rightHands[i]->GetPosition().x < this->GetPosition().x - 40)
                    rightHands[i]->SetVx(80 * i);
                else rightHands[i]->SetVx(0);
            }
            rightHands[i]->SetVy(rightHands[i]->GetVy() + this->vy);
            rightHands[i]->SetVx(rightHands[i]->GetVx() + this->vx);
        }
        break;
    case 3:
        for (int i = 0; i < 5; i++)
        {
            if (rightHands[i]->GetPosition().x > this->GetPosition().x - 40 - 32 * i)
                rightHands[i]->SetVx(-80 * i);
            else rightHands[i]->SetVx(0);
            rightHands[i]->SetVx(rightHands[i]->GetVx() + this->vx);
            rightHands[i]->SetVy(this->vy);
        }
        break;
    case 4:
        for (int i = 0; i < 5; i++)
        {
            if (rightHands[i]->GetPosition().y > this->GetPosition().y - 40 * i)
                rightHands[i]->SetVy(-80 * i);
            else rightHands[i]->SetVy(0);
            rightHands[i]->SetVy(rightHands[i]->GetVy() + this->vy);
            rightHands[i]->SetVx(this->vx);
        }
        break;
    default:
        for (int i = 0; i < 5; i++)
        {
            if (rightHands[i]->GetPosition().y < this->GetPosition().y + 40 * i)
                rightHands[i]->SetVy(80 * i);
            else rightHands[i]->SetVy(0);
            rightHands[i]->SetVy(rightHands[i]->GetVy() + this->vy);
            rightHands[i]->SetVx(this->vx);
        }
        break;
    }
    if (mMoveHandRightTime >= 1.5f && (mMoveHandRightStep == 1 || mMoveHandRightStep == 2))
    {
        mMoveHandRightStep++;
        mMoveHandRightTime = 0;
    }
    else if (mMoveHandRightTime >= 0.75f && (mMoveHandRightStep != 1 && mMoveHandRightStep != 2))
    {
        mMoveHandRightStep++;
        mMoveHandRightTime = 0;
    }
}

void Boss::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    if (impactor->Tag == EntityTypes::Bullets)
    {
        mHp--;
        if (mHp == 0)
            GameSound::GetInstance()->Stop("boss");
    }
    else
    {
        switch (side)
        {
        case Entity::Left:
            if (impactor->Tag == EntityTypes::Player)
            {

            }
            else if (impactor->Tag != EntityTypes::Ladder)
            {
                this->AddPosition(1, 0);
                this->SetVx(-this->GetVx());
            }
            break;

        case Entity::Right:
            if (impactor->Tag == EntityTypes::Player)
            {

            }
            else if (impactor->Tag != EntityTypes::Ladder)
            {
                this->AddPosition(-1, 0);
                this->SetVx(-this->GetVx());
            }
            break;

        case Entity::Top:
            this->SetVy(40);
            break;

        case Entity::Bottom:
        case Entity::BottomRight:
        case Entity::BottomLeft:
            if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
            {
                this->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
                this->SetVy(-40);
            }
            break;

        default:
            break;
        }
    }
}

void Boss::Draw(D3DXVECTOR2 transform)
{
    mAnimation->Draw(D3DXVECTOR3(posX, posY, 0), RECT(), D3DXVECTOR2(), transform);
    for (int i = 0; i < 5; i++)
    {
        leftHands[i]->Draw(transform);
        rightHands[i]->Draw(transform);
    }
    for (int i = 0; i < mBullets.size(); i++)
    {
        mBullets[i]->Draw(mBullets[i]->GetPosition(), RECT(), D3DXVECTOR2(), transform);
    }
}

vector<BossHand*> Boss::GetBossHandLeft()
{
    return leftHands;
}
vector<BossHand*> Boss::GetBossHandRight()
{
    return rightHands;
}

const char* Boss::FileName()
{
    return "Assets/Boss/boss.png";
}

int Boss::TotalFrame()
{
    return 4;
}

int Boss::Column()
{
    return 4;
}