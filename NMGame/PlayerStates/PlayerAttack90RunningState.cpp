#include "PlayerAttack90RunningState.h"
#include "PlayerAttacking90State.h"
#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerJumpingState.h"
#include "../GameDefines.h"

PlayerAttack90RunningState::PlayerAttack90RunningState(PlayerData* playerData)
{
    this->mPlayerData = playerData;

    acceleratorX = 28.0f;
}


PlayerAttack90RunningState::~PlayerAttack90RunningState()
{
}

void PlayerAttack90RunningState::Update(float dt)
{

}

void PlayerAttack90RunningState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        if (keys[VK_UP])
        {
            if (mPlayerData->player->allowMoveRight)
            {
                mPlayerData->player->SetReverse(false);

                //di chuyen sang phai
                /*if (this->mPlayerData->player->GetVx() < Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->mPlayerData->player->AddVx(acceleratorX);

                    if (this->mPlayerData->player->GetVx() >= Define::PLAYER_MAX_RUNNING_SPEED)
                    {
                        this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
                    }
                }*/
                this->mPlayerData->player->SetVx(Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
        else
        {
            this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
            return;
        }
    }
    else if (keys[VK_LEFT])
    {
        if (keys[VK_UP])
        {
            if (mPlayerData->player->allowMoveLeft)
            {
                mPlayerData->player->SetReverse(true);

                //di chuyen sang trai
                /*if (this->mPlayerData->player->GetVx() > -Define::PLAYER_MAX_RUNNING_SPEED)
                {
                    this->mPlayerData->player->AddVx(-acceleratorX);

                    if (this->mPlayerData->player->GetVx() < -Define::PLAYER_MAX_RUNNING_SPEED)
                    {
                        this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
                    }
                }*/
                this->mPlayerData->player->SetVx(-Define::PLAYER_MAX_RUNNING_SPEED);
            }
        }
        else
        {
            this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
            return;
        }
    }
    else
    {
        if (keys[VK_UP])
        {
            this->mPlayerData->player->SetState(new PlayerAttacking90State(this->mPlayerData));
            return;
        }
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        return;
    }
}

void PlayerAttack90RunningState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

            this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
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
            this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        }
        return;
    }

    case Entity::Top:
        break;

    case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
    {
        this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

        this->mPlayerData->player->SetVy(0);

        return;
    }
    }
}

PlayerState::StateName PlayerAttack90RunningState::GetState()
{
    return PlayerState::Attack90Running;
}

