#pragma once
#include "../PlayerState.h"
#include "../Player.h"

class PlayerAttackRunningState : public PlayerState
{
public:
    PlayerAttackRunningState(PlayerData* playerData);
    ~PlayerAttackRunningState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorX;
};