#pragma once
#include "Player.h"
class PlayerOverhead : public Player
{
public:
    PlayerOverhead();
    ~PlayerOverhead();

    void OnKeyPressed(int key);

    void OnKeyUp(int key);

};

