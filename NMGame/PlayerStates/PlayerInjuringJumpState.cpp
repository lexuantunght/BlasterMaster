#include "PlayerInjuringJumpState.h"
#include "PlayerInjuringFallState.h"
#include "../GameDefines.h"
PlayerInjuringJumpState::PlayerInjuringJumpState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVy(Define::PLAYER_MIN_JUMP_VELOCITY);

    acceleratorY = 10.0f;
    acceleratorX = 6.0f;

    noPressed = false;
    allowMoveLeft = true;
    allowMoveRight = true;
}

PlayerInjuringJumpState::~PlayerInjuringJumpState()
{

}

void PlayerInjuringJumpState::Update(float dt)
{
    this->mPlayerData->player->AddVy(acceleratorY);

    if (mPlayerData->player->GetVy() >= 0)
    {
        mPlayerData->player->SetState(new PlayerInjuringFallState(this->mPlayerData));

        return;
    }

    if (noPressed)
    {
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            //player dang di chuyen sang ben trai      
            if (mPlayerData->player->GetVx() < 0)
            {
                this->mPlayerData->player->AddVx(acceleratorX);

                if (mPlayerData->player->GetVx() > 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
        else if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            //player dang di chuyen sang phai   
            if (mPlayerData->player->GetVx() > 0)
            {
                this->mPlayerData->player->AddVx(-acceleratorX);

                if (mPlayerData->player->GetVx() < 0)
                    this->mPlayerData->player->SetVx(0);
            }
        }
    }
}

PlayerState::StateName PlayerInjuringJumpState::GetState()
{
    return PlayerState::InjuringJump;
}