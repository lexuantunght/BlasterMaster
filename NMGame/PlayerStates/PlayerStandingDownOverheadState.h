#pragma once
#include "../PlayerState.h"
#include "../Player.h"
#include "PlayerStandingOverheadState.h"

class PlayerStandingDownOverheadState : public PlayerStandingOverheadState
{
public:
    PlayerStandingDownOverheadState(PlayerData* playerData);
    ~PlayerStandingDownOverheadState();

    StateName GetState();
};

