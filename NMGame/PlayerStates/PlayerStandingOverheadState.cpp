#include "PlayerStandingOverheadState.h"
#include "PlayerRunningOverheadState.h"
#include "PlayerRunningDownOverheadState.h"
#include "PlayerRunningUpOverheadState.h"
#include "../Player.h"

PlayerStandingOverheadState::PlayerStandingOverheadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}

PlayerStandingOverheadState::PlayerStandingOverheadState()
{
    
}

PlayerStandingOverheadState::~PlayerStandingOverheadState()
{
}

void PlayerStandingOverheadState::Update(float dt)
{

}

void PlayerStandingOverheadState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        this->mPlayerData->player->SetState(new PlayerRunningOverheadState(this->mPlayerData));
        return;
    }
    if (keys[VK_UP])
    {
        this->mPlayerData->player->SetState(new PlayerRunningUpOverheadState(this->mPlayerData));
        return;
    }
    if (keys[VK_DOWN])
    {
        this->mPlayerData->player->SetState(new PlayerRunningDownOverheadState(this->mPlayerData));
        return;
    }
}


PlayerState::StateName PlayerStandingOverheadState::GetState()
{
    return PlayerState::StandingOverhead;
}