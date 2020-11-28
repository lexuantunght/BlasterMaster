#include "PlayerInjuringOverheadState.h"
#include "PlayerStandingOverheadState.h"
PlayerInjuringOverheadState::PlayerInjuringOverheadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
    this->mTimeExist = 0.5f;
    this->mCurrentTime = 0;
}


PlayerInjuringOverheadState::~PlayerInjuringOverheadState()
{
}

void PlayerInjuringOverheadState::Update(float dt)
{
    if (mCurrentTime >= mTimeExist)
    {
        this->mPlayerData->player->SetState(new PlayerStandingOverheadState(this->mPlayerData));
        return;
    }
    else
    {
        mCurrentTime += dt;
    }
}

void PlayerInjuringOverheadState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        //this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        if (this->mPlayerData->player->allowMoveRight)
        {
            mPlayerData->player->SetReverse(false);
            this->mPlayerData->player->SetVx(140);
        }
        return;
    }
    else if (keys[VK_LEFT])
    {
        if (this->mPlayerData->player->allowMoveLeft)
        {
            mPlayerData->player->SetReverse(true);
            this->mPlayerData->player->SetVx(-140);
        }
        return;
    }
    else
    {
        this->mPlayerData->player->SetVx(0);
    }
}

void PlayerInjuringOverheadState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);
    if (impactor->Tag != Entity::EntityTypes::Dangers)
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

PlayerState::StateName PlayerInjuringOverheadState::GetState()
{
    return PlayerState::InjuringOverhead;
}