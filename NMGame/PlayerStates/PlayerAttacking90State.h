#pragma once
#include "../Player.h"
#include "../PlayerState.h"

class PlayerAttacking90State : public PlayerState
{
public:
    PlayerAttacking90State(PlayerData* playerData);
    ~PlayerAttacking90State();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();
protected:

};