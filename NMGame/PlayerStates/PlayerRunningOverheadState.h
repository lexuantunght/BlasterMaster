#pragma once
#include "../Player.h"
#include "../PlayerState.h"
class PlayerRunningOverheadState : public PlayerState
{
public:
    PlayerRunningOverheadState(PlayerData* playerData);
    PlayerRunningOverheadState();
    ~PlayerRunningOverheadState();

    void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    //do bien tien van toc sau moi frame tinh bang pixel / s
    float acceleratorX;
};

