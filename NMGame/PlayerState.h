#pragma once
#include "PlayerData.h"
#include "Entity.h"
#include <map>

class PlayerState
{
public:
    enum StateName
    {
        Standing,
        Running,
        Falling,
        Jumping,
        Flipping,
        Attacking,
        AttackRunning,
        Attacking90,
        Attack90Running,
        Die,
        Injuring,
        InjuringJump,
        InjuringFall,
        Climbing,
        RunningOverhead,
        StandingOverhead,
        StandingUpOverhead,
        StandingDownOverhead,
        RunningUpOverhead,
        RunningDownOverhead,
        InjuringOverhead,
        InjuringUpOverhead,
        InjuringDownOverhead,
        Dead,
        OverheadDead
    };

    PlayerState(PlayerData* playerData);
    PlayerState();
    ~PlayerState();

    virtual void Update(float dt);

    virtual void HandleKeyboard(std::map<int, bool> keys);

    //side va cham voi player
    virtual void OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data);

    //ham thuan ao bat buoc phai ke thua
    virtual StateName GetState() = 0;

protected:
    PlayerData* mPlayerData;
};
