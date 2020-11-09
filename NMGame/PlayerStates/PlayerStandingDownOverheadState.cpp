#include "PlayerStandingDownOverheadState.h"
#include "PlayerRunningOverheadState.h"
#include "PlayerRunningDownOverheadState.h"
#include "PlayerRunningUpOverheadState.h"
#include "../Player.h"

PlayerStandingDownOverheadState::PlayerStandingDownOverheadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerStandingDownOverheadState::~PlayerStandingDownOverheadState()
{
}


PlayerState::StateName PlayerStandingDownOverheadState::GetState()
{
    return PlayerState::StandingDownOverhead;
}