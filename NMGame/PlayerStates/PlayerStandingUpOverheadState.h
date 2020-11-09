#pragma once
#include "PlayerStandingOverheadState.h"
class PlayerStandingUpOverheadState : public PlayerStandingOverheadState
{
public:
    PlayerStandingUpOverheadState(PlayerData* playerData);
    ~PlayerStandingUpOverheadState();

    StateName GetState();
};

