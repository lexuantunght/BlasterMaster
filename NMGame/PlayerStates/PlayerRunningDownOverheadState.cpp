#include "PlayerRunningDownOverheadState.h"
#include "PlayerStandingDownOverheadState.h"

PlayerRunningDownOverheadState::PlayerRunningDownOverheadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;

    acceleratorX = 28.0f;
}


PlayerRunningDownOverheadState::~PlayerRunningDownOverheadState()
{
}

void PlayerRunningDownOverheadState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_DOWN])
    {
        if (mPlayerData->player->allowMoveDown)
        {
            this->mPlayerData->player->SetVy(140);
            if (keys[VK_RIGHT])
            {
                this->mPlayerData->player->SetVx(140);
            }
            else if (keys[VK_LEFT])
            {
                this->mPlayerData->player->SetVx(-140);
            }
            else this->mPlayerData->player->SetVx(0);
        }
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingDownOverheadState(this->mPlayerData));
        return;
    }
}

PlayerState::StateName PlayerRunningDownOverheadState::GetState()
{
    return PlayerState::RunningDownOverhead;
}