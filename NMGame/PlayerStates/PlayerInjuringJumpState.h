#pragma once
#include "../PlayerState.h"
#include "PlayerJumpingState.h"
class PlayerInjuringJumpState : public PlayerJumpingState
{
public:
    PlayerInjuringJumpState(PlayerData* playerData);
    ~PlayerInjuringJumpState();

    virtual StateName GetState();
};

