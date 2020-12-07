#include "PlayerOverheadDeadState.h"
PlayerOverheadDeadState::PlayerOverheadDeadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
}


PlayerOverheadDeadState::~PlayerOverheadDeadState()
{
}

void PlayerOverheadDeadState::Update(float dt)
{
    /*if (countTime >= 0.2f)
    {
        this->mPlayerData->player->isDead = true;
        return;
    }
    countTime += dt;*/
}

void PlayerOverheadDeadState::HandleKeyboard(std::map<int, bool> keys)
{

}

void PlayerOverheadDeadState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{

}


PlayerState::StateName PlayerOverheadDeadState::GetState()
{
    return PlayerState::OverheadDead;
}