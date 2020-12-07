#pragma once
#include "../PlayerState.h"
#include "PlayerFallingState.h"
class PlayerInjuringFallState : public PlayerFallingState
{
public:
    PlayerInjuringFallState(PlayerData* playerData);
    ~PlayerInjuringFallState();
    void Update(float dt);
    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);
    virtual StateName GetState();
};