#include "PlayerRunningUpOverheadState.h"
#include "PlayerStandingUpOverheadState.h"

PlayerRunningUpOverheadState::PlayerRunningUpOverheadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;

    acceleratorX = 28.0f;
}


PlayerRunningUpOverheadState::~PlayerRunningUpOverheadState()
{
}


void PlayerRunningUpOverheadState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_UP])
    {
        if (mPlayerData->player->allowMoveUp)
        {
            this->mPlayerData->player->SetVy(-140);
            if (keys[VK_RIGHT] && this->mPlayerData->player->allowMoveRight)
            {
                this->mPlayerData->player->SetVx(140);
            }
            else if (keys[VK_LEFT] && this->mPlayerData->player->allowMoveLeft)
            {
                this->mPlayerData->player->SetVx(-140);
            }
            else this->mPlayerData->player->SetVx(0);
        }
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingUpOverheadState(this->mPlayerData));
        return;
    }
}

PlayerState::StateName PlayerRunningUpOverheadState::GetState()
{
    return PlayerState::RunningUpOverhead;
}