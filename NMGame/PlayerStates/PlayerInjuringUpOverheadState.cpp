#include "PlayerInjuringUpOverheadState.h"
#include "PlayerStandingUpOverheadState.h"
PlayerInjuringUpOverheadState::PlayerInjuringUpOverheadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
    this->mTimeExist = 0.5f;
    this->mCurrentTime = 0;
}


PlayerInjuringUpOverheadState::~PlayerInjuringUpOverheadState()
{
}

void PlayerInjuringUpOverheadState::Update(float dt)
{
    if (mCurrentTime >= mTimeExist)
    {
        this->mPlayerData->player->SetState(new PlayerStandingUpOverheadState(this->mPlayerData));
        return;
    }
    else
    {
        mCurrentTime += dt;
    }
}

void PlayerInjuringUpOverheadState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_UP])
    {
        //this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        if (this->mPlayerData->player->allowMoveUp)
        {
            this->mPlayerData->player->SetVy(-140);
            if (keys[VK_LEFT])
            {
                this->mPlayerData->player->SetVx(-140);
            }
            else this->mPlayerData->player->SetVx(0);
        }
        return;
    }
    else if (keys[VK_DOWN])
    {
        if (this->mPlayerData->player->allowMoveDown)
        {
            this->mPlayerData->player->SetVy(140);
            if (keys[VK_LEFT])
            {
                this->mPlayerData->player->SetVx(-140);
            }
            else this->mPlayerData->player->SetVx(0);
        }
        return;
    }
    else
    {
        this->mPlayerData->player->SetVy(0);
    }
}

void PlayerInjuringUpOverheadState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

    switch (side)
    {
    case Entity::Left:
    {
        //va cham phia ben trai player
        if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            this->mPlayerData->player->allowMoveLeft = false;

            //day Player ra phia ben phai de cho player khong bi xuyen qua object
            this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

        }

        return;
    }

    case Entity::Right:
    {
        //va cham phia ben phai player
        if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            this->mPlayerData->player->allowMoveRight = false;
            this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
        }
        return;
    }
<<<<<<< HEAD
=======

>>>>>>> e9bd6a8710eb6f129c14ed88a6a5eec9b551337a
    case Entity::Top:
    {
        this->mPlayerData->player->allowMoveUp = false;
        this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.top - data.RegionCollision.bottom));
        return;
    }

    case Entity::Bottom:
    case Entity::BottomLeft:
    case Entity::BottomRight:
    {
        this->mPlayerData->player->allowMoveDown = false;
        this->mPlayerData->player->AddPosition(0, (data.RegionCollision.top - data.RegionCollision.bottom));
        return;
    }
    }
}

PlayerState::StateName PlayerInjuringUpOverheadState::GetState()
{
    return PlayerState::InjuringUpOverhead;
}