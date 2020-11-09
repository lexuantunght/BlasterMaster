#pragma once
#include "../Player.h"
#include "../PlayerState.h"

class PlayerAttackingState : public PlayerState
{
public:
    PlayerAttackingState(PlayerData* playerData);
    ~PlayerAttackingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();
protected:

};

