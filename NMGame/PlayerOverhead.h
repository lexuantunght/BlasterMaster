#pragma once
#include "Player.h"
class PlayerOverhead : public Player
{
public:
    PlayerOverhead();
    ~PlayerOverhead();
    void DrawPower(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));
    void OnKeyPressed(int key);

    void OnKeyUp(int key);
};

