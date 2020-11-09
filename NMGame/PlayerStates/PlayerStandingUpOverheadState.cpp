#include "PlayerStandingUpOverheadState.h"
#include "PlayerRunningOverheadState.h"
#include "PlayerRunningDownOverheadState.h"
#include "PlayerRunningUpOverheadState.h"
#include "../Player.h"

PlayerStandingUpOverheadState::PlayerStandingUpOverheadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerStandingUpOverheadState::~PlayerStandingUpOverheadState()
{
}


PlayerState::StateName PlayerStandingUpOverheadState::GetState()
{
    return PlayerState::StandingUpOverhead;
}