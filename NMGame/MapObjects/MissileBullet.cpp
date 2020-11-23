#include "MissileBullet.h"
#include "../Scenes/FirstScene.h"
MissileBullet::MissileBullet(D3DXVECTOR3 position, int angle)
{
    mAnimation = new Animation("Assets/missileBullet.png", 2, 1, 2, 0.1f);
    if (angle == 0)
    {
        this->SetVx(180);
    }
    else
    {
        mAnimation->FlipVertical(true);
        this->SetVx(-180);
    }

    mTimeExistMaximum = 3.0f;

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    countTimeToGoto = 0;
    countTimeChange = 0;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::Bullets;
}

MissileBullet::~MissileBullet()
{

}

int MissileBullet::FindIndexMinDistance()
{
    if (FirstScene::mEnemies.size() > 0)
    {
        int index = 0;
        double minLength = sqrt(((double)FirstScene::mEnemies.at(0)->GetPosition().x - this->GetPosition().x) * (FirstScene::mEnemies.at(0)->GetPosition().x - this->GetPosition().x)
            + ((double)FirstScene::mEnemies.at(0)->GetPosition().y - this->GetPosition().y) * (FirstScene::mEnemies.at(0)->GetPosition().y - this->GetPosition().y));
        for (int i = 0; i < FirstScene::mEnemies.size(); i++)
        {
            double tmp = sqrt(((double)FirstScene::mEnemies.at(i)->GetPosition().x - this->GetPosition().x) * (FirstScene::mEnemies.at(i)->GetPosition().x - this->GetPosition().x)
                + ((double)FirstScene::mEnemies.at(i)->GetPosition().y - this->GetPosition().y) * (FirstScene::mEnemies.at(i)->GetPosition().y - this->GetPosition().y));
            if (tmp < minLength)
                index = i;
        }
        return index;
    }
    else return -1;
}

void MissileBullet::GotoEnemy()
{
    if (FirstScene::mEnemies.at(minIndex)->GetPosition().x > this->GetPosition().x + 10)
        this->SetVx(120);
    else if (FirstScene::mEnemies.at(minIndex)->GetPosition().x < this->GetPosition().x - 10) this->SetVx(-120);
    else this->SetVx(0);

    if (FirstScene::mEnemies.at(minIndex)->GetPosition().y > this->GetPosition().y + 10)
        this->SetVy(80);
    else if (FirstScene::mEnemies.at(minIndex)->GetPosition().y < this->GetPosition().y - 10) this->SetVy(-80);
    else this->SetVy(0);

    if (vx > 0)
    {
        mAnimation->FlipVertical(false);
    }
    else
    {
        mAnimation->FlipVertical(true);
    }
    
    if (vx == 0)
    {
        if (mAnimation->IsFlipVertical())
        {
            if (vy > 0)
                mAnimation->SetRotation(-3.14 / 2);
            else mAnimation->SetRotation(3.14 / 2);
        }
        else
        {
            if (vy > 0)
                mAnimation->SetRotation(-3.14 / 2);
            else mAnimation->SetRotation(3.14 / 2);
        }
    }
    else mAnimation->SetRotation(0);
}

void MissileBullet::Update(float dt)
{
    //goto a enemy
    if (countTimeChange >= 0.25f)
    {
        GotoEnemy();
        countTimeChange = 0;
    }
    else countTimeChange += dt;

    if (countTimeToGoto >= 0.5f)
    {
        minIndex = FindIndexMinDistance();
        countTimeToGoto = 0;
    }
    else countTimeToGoto += dt;

    if (mIsValid && mTimeExist >= mTimeExistMaximum)
    {
        mIsValid = false;
    }

    mAnimation->SetPosition(Entity::GetPosition());
    mAnimation->Update(dt);
    mTimeExist += dt;
    Entity::Update(dt);
}

void MissileBullet::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    if (impactor->Tag != EntityTypes::Static && impactor->Tag != EntityTypes::Ladder)
        mIsValid = false;
}