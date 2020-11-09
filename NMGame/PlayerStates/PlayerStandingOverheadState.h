#pragma once
#include "../Player.h"
#include "../PlayerState.h"
class PlayerStandingOverheadState : public PlayerState
{
public:
    PlayerStandingOverheadState(PlayerData* playerData);
    PlayerStandingOverheadState();
    ~PlayerStandingOverheadState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
};

