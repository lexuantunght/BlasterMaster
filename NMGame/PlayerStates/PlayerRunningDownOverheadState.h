#pragma once
#include "PlayerRunningOverheadState.h"

class PlayerRunningDownOverheadState : public PlayerRunningOverheadState
{
public:
    PlayerRunningDownOverheadState(PlayerData* playerData);
    ~PlayerRunningDownOverheadState();

    void HandleKeyboard(std::map<int, bool> keys);

    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorX;
};

