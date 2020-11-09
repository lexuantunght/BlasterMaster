#include "PlayerClimbingState.h"
#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerFallingState.h"
#include "PlayerAttackRuningState.h"
#include "PlayerAttack90RunningState.h"
#include "PlayerJumpingState.h"
#include "../GameDefines.h"

PlayerClimbingState::PlayerClimbingState(PlayerData* playerData)
{
    this->mPlayerData = playerData;

    acceleratorY = -14.0f;
    allowClimb = true;
    this->mPlayerData->player->allowMoveLeft = false;
    this->mPlayerData->player->allowMoveRight = false;
}


PlayerClimbingState::~PlayerClimbingState()
{
}

void PlayerClimbingState::Update(float dt)
{

}

void PlayerClimbingState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_UP])
    {
        if (allowClimb)
            this->mPlayerData->player->SetVy(-140);
    }
    else if (keys[VK_DOWN])
    {
        this->mPlayerData->player->SetVy(140);
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        return;
    }
}

void PlayerClimbingState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    //lay phia va cham so voi player
    //GameCollision::SideCollisions side = GameCollision::getSideCollision(this->mPlayerData->player, data);

    switch (side)
    {
    case Entity::Left:
    {
        //va cham phia ben trai player
        if (this->mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            this->mPlayerData->player->allowMoveLeft = false;

            //day Player ra phia ben phai de cho player khong bi xuyen qua object
            this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);

            this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        }

        return;
    }

    case Entity::Right:
    {
        //va cham phia ben phai player
        if (this->mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            this->mPlayerData->player->allowMoveRight = false;
            this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
            this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        }
        return;
    }

    case Entity::Top:
        this->mPlayerData->player->AddPosition(0, 10);
        this->mPlayerData->player->SetVy(0);
        allowClimb = false;
        break;

    case Entity::Bottom: case Entity::BottomLeft: case Entity::BottomRight:
    {
        this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

        this->mPlayerData->player->SetVy(0);

        return;
    }
    }
}

PlayerState::StateName PlayerClimbingState::GetState()
{
    return PlayerState::Climbing;
}