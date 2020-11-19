#include "PlayerFlippingState.h"
#include "../Player.h"
#include "PlayerFallingState.h"
#include "PlayerAttackingState.h"
#include "PlayerAttacking90State.h"
#include "PlayerJumpingState.h"
#include "PlayerRunningState.h"
#include "PlayerInjuringState.h"
#include "PlayerClimbingState.h"
#include "../GameDefines.h"

PlayerFlippingState::PlayerFlippingState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
    mCurrentTime = 0;
    mTimeExist = 0.32f;
}


PlayerFlippingState::~PlayerFlippingState()
{
}

void PlayerFlippingState::Update(float dt)
{
    if (mCurrentTime >= mTimeExist)
    {
        this->mPlayerData->player->SetReverse(!mPlayerData->player->GetReverse());
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        mCurrentTime = 0;
        return;
    }
    else
    {
        mCurrentTime += dt;
    }
}

void PlayerFlippingState::HandleKeyboard(std::map<int, bool> keys)
{
    
}


PlayerState::StateName PlayerFlippingState::GetState()
{
    return PlayerState::Flipping;
}
