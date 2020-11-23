#include "MissileBullet.h"
MissileBullet::MissileBullet(D3DXVECTOR3 position, int angle)
{
    if (angle == 0)
    {
        mAnimation = new Animation("Assets/missileBullet0.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(240);
    }
    else
    {
        mAnimation = new Animation("Assets/missileBullet180.png", TotalFrame(), Row(), Column(), SecondPerFrame());
        this->SetVx(-240);
    }

    mTimeExistMaximum = 2.0f;

    SetPosition(position);
    mStartedPosition = position;
    mTimeExist = 0;
    mIsValid = true;

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());
    Tag = Entity::EntityTypes::Bullets;
}

MissileBullet::~MissileBullet()
{

}

void MissileBullet::SetMission(vector<D3DXVECTOR3> listMission)
{
    this->listMission.clear();
    for (int i = 0; i < listMission.size(); i++)
    {
        this->listMission.push_back(listMission.at(i));
    }
}

int MissileBullet::FindIndexMinDistance()
{
    if (listMission.size() > 0)
    {
        int index = 0;
        double minLength = sqrt(((double)listMission.at(0).x - this->GetPosition().x) * (listMission.at(0).x - this->GetPosition().x)
            + ((double)listMission.at(0).y - this->GetPosition().y) * (listMission.at(0).y - this->GetPosition().y));
        for (int i = 1; i < listMission.size(); i++)
        {
            double tmp = sqrt(((double)listMission.at(i).x - this->GetPosition().x) * (listMission.at(i).x - this->GetPosition().x)
                + ((double)listMission.at(i).y - this->GetPosition().y) * (listMission.at(i).y - this->GetPosition().y));
            if (tmp < minLength)
                index = i;
        }
        return index;
    }
    else return -1;
}

void MissileBullet::GotoEnemy()
{
    int index = FindIndexMinDistance();
    if (index == -1) return;
    this->SetVx((listMission.at(index).x - this->GetPosition().x) / 5);
    this->SetVy((listMission.at(index).y - this->GetPosition().y) / 5);
}

void MissileBullet::Update(float dt)
{
    //goto a enemy
    GotoEnemy();
    if (mIsValid && mTimeExist >= mTimeExistMaximum)
    {
        mIsValid = false;
    }
    mAnimation->Update(dt);
    mTimeExist += dt;
    Entity::Update(dt);
}

void MissileBullet::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{

}