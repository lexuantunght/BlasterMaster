#pragma once
#include "../PlayerState.h"
#include "../Player.h"


class PlayerFallingState : public PlayerState
{
public:
    PlayerFallingState(PlayerData *playerData);
    ~PlayerFallingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);
    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorY;
    float acceleratorX;

    //neu nhu van toc ban dau = khong thi se khong cho giam toc do
    bool allowMoveX;

    bool isLeftOrRightKeyPressed;
};

