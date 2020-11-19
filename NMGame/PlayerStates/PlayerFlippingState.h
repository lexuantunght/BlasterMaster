#pragma once
#include "../PlayerState.h"
#include "../Player.h"

class PlayerFlippingState : public PlayerState
{
public:
    PlayerFlippingState(PlayerData* playerData);
    ~PlayerFlippingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
    float mTimeExist;
    float mCurrentTime;
};