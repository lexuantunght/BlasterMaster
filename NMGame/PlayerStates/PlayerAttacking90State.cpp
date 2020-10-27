#include "PlayerAttacking90State.h"
#include "PlayerAttack90RunningState.h"
#include "PlayerStandingState.h"
#include "../GameDefines.h"
#include "../MapObjects/Bullet.h"

PlayerAttacking90State::PlayerAttacking90State(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}

PlayerAttacking90State::~PlayerAttacking90State()
{

}

void PlayerAttacking90State::Update(float dt)
{

}

void PlayerAttacking90State::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_UP])
    {
        if (keys[VK_RIGHT] || keys[VK_LEFT])
        {
            this->mPlayerData->player->SetState(new PlayerAttack90RunningState(this->mPlayerData));
            return;
        }
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        return;
    }
}

PlayerState::StateName PlayerAttacking90State::GetState()
{
    return PlayerState::Attacking90;
}
