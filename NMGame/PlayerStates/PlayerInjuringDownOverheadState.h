#pragma once
#include "../PlayerState.h"
class PlayerInjuringDownOverheadState : public PlayerState
{
public:
    PlayerInjuringDownOverheadState(PlayerData* playerData);
    ~PlayerInjuringDownOverheadState();

    void Update(float dt);

    void HandleKeyboard(std::map<int, bool> keys);

    void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    virtual StateName GetState();
protected:
    float mTimeExist;
    float mCurrentTime;
};

