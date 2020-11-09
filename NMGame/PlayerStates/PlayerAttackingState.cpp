#include "PlayerAttackingState.h"
#include "PlayerAttackRuningState.h"
#include "PlayerStandingState.h"
#include "../GameDefines.h"
#include "../MapObjects/Bullet.h"

PlayerAttackingState::PlayerAttackingState(PlayerData* playerData)
{
	this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}

PlayerAttackingState::~PlayerAttackingState()
{

}

void PlayerAttackingState::Update(float dt)
{

}

void PlayerAttackingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[0x4B])
    {
        if (keys[VK_RIGHT] || keys[VK_LEFT])
        {
            this->mPlayerData->player->SetState(new PlayerAttackRunningState(this->mPlayerData));
            return;
        }
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        return;
    }
}

PlayerState::StateName PlayerAttackingState::GetState()
{
    return PlayerState::Attacking;
}