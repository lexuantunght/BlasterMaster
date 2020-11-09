#pragma once
#include "PlayerInjuringState.h"
#include "../PlayerState.h"
class PlayerInjuringOverheadState : public PlayerState
{
public:
    PlayerInjuringOverheadState(PlayerData* playerData);
    ~PlayerInjuringOverheadState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();

protected:
    float mTimeExist;
    float mCurrentTime;
};

