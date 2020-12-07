#include "PlayerDeadState.h"
#include <string>
PlayerDeadState::PlayerDeadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerDeadState::~PlayerDeadState()
{
}

void PlayerDeadState::Update(float dt)
{
    /*if (countTime >= 0.2f)
    {
        this->mPlayerData->player->isDead = true;
        return;
    }
    countTime += dt;*/
}

void PlayerDeadState::HandleKeyboard(std::map<int, bool> keys)
{
    
}

void PlayerDeadState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}


PlayerState::StateName PlayerDeadState::GetState()
{
    return PlayerState::Dead;
}