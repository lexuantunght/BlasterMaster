#pragma once
#include "PlayerRunningOverheadState.h"
class PlayerRunningUpOverheadState : public PlayerRunningOverheadState
{
public:
    PlayerRunningUpOverheadState(PlayerData* playerData);
    ~PlayerRunningUpOverheadState();

    void HandleKeyboard(std::map<int, bool> keys);

    StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorX;
};

