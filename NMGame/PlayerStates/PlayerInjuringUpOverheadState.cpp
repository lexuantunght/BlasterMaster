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
    }
}

PlayerState::StateName PlayerInjuringUpOverheadState::GetState()
{
    return PlayerState::InjuringUpOverhead;
}