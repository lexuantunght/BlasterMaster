#pragma once
#include "../PlayerState.h"
#include "../Player.h"

class PlayerInjuringState : public PlayerState
{
public:
    PlayerInjuringState(PlayerData* playerData);
    ~PlayerInjuringState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    float mTimeExist;
    float mCurrentTime;
};