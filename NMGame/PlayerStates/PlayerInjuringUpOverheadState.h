#pragma once
#include "../PlayerState.h"
class PlayerInjuringUpOverheadState : public PlayerState
{
public:
    PlayerInjuringUpOverheadState(PlayerData* playerData);
    ~PlayerInjuringUpOverheadState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();
protected:
    float mTimeExist;
    float mCurrentTime;
};

