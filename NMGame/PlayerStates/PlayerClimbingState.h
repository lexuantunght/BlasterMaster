#pragma once
#include "../PlayerState.h"
#include "../Player.h"

class PlayerClimbingState : public PlayerState
{
public:
    PlayerClimbingState(PlayerData* playerData);
    ~PlayerClimbingState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorY;
    bool allowClimb;
};