#include "PlayerInjuringJumpState.h"
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

PlayerState::StateName PlayerInjuringJumpState::GetState()
{
    return PlayerState::InjuringJump;
}