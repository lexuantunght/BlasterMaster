#include "PlayerStandingState.h"
#include "../Player.h"
#include "PlayerFallingState.h"
#include "PlayerAttackingState.h"
#include "PlayerAttacking90State.h"
#include "PlayerJumpingState.h"
#include "PlayerRunningState.h"
#include "PlayerInjuringState.h"
#include "PlayerClimbingState.h"
#include "PlayerFlippingState.h"
#include "../GameDefines.h"

PlayerStandingState::PlayerStandingState(PlayerData *playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerStandingState::~PlayerStandingState()
{
}

void PlayerStandingState::Update(float dt)
{

}

void PlayerStandingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_LEFT] || keys[VK_RIGHT])
    {
        //this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        if (!mPlayerData->player->isShowJason && ((keys[VK_LEFT] && !mPlayerData->player->GetReverse()) || (keys[VK_RIGHT] && mPlayerData->player->GetReverse())))
        {
            this->mPlayerData->player->SetState(new PlayerFlippingState(this->mPlayerData));
            return;
        }
        else this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        return;
    }
    if (keys[VK_UP])
    {
        if (this->mPlayerData->player->isShowJason)
        {
            if (this->mPlayerData->player->isOnLadder)
            {
                this->mPlayerData->player->SetState(new PlayerClimbingState(this->mPlayerData));
            }
            return;
        }
        this->mPlayerData->player->SetState(new PlayerAttacking90State(this->mPlayerData));
        return;
    }
    if (keys[VK_DOWN])
    {
        if (this->mPlayerData->player->isShowJason)
        {
            if (this->mPlayerData->player->isOnLadder)
            {
                this->mPlayerData->player->SetState(new PlayerClimbingState(this->mPlayerData));
            }
            return;
        }
    }
    if (keys[0x4B])
    {
        this->mPlayerData->player->SetState(new PlayerAttackingState(this->mPlayerData));
        return;
    }
}


PlayerState::StateName PlayerStandingState::GetState()
{
    return PlayerState::Standing;
}
