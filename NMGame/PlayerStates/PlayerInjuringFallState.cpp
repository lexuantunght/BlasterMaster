#include "PlayerInjuringFallState.h"
#include "../GameDefines.h"
PlayerInjuringFallState::PlayerInjuringFallState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    acceleratorY = 40.0f;
    acceleratorX = 5.0f;
    isLeftOrRightKeyPressed = false;

    if (this->mPlayerData->player->GetVx() == 0)
    {
        allowMoveX = false;
    }
    else
    {
        allowMoveX = true;
    }
}

PlayerInjuringFallState::~PlayerInjuringFallState()
{

}

void PlayerInjuringFallState::Update(float dt)
{
    this->mPlayerData->player->AddVy(acceleratorY);

    if (mPlayerData->player->GetVy() > Define::PLAYER_MAX_JUMP_VELOCITY)
    {
        mPlayerData->player->SetVy(Define::PLAYER_MAX_JUMP_VELOCITY);
    }
}

void PlayerInjuringFallState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
{
    switch (side)
    {
    case Entity::Left:
        if (mPlayerData->player->getMoveDirection() == Player::MoveToLeft)
        {
            this->mPlayerData->player->AddPosition(data.RegionCollision.right - data.RegionCollision.left, 0);
            this->mPlayerData->player->SetVx(0);
        }
        break;

    case Entity::Right:
        if (mPlayerData->player->getMoveDirection() == Player::MoveToRight)
        {
            this->mPlayerData->player->AddPosition(-(data.RegionCollision.right - data.RegionCollision.left), 0);
            this->mPlayerData->player->SetVx(0);
        }
        break;

    case Entity::Top:
        break;

    case Entity::Bottom:
    case Entity::BottomRight:
    case Entity::BottomLeft:
        if (data.RegionCollision.right - data.RegionCollision.left >= 8.0f)
        {
            if (impactor->Tag != Entity::EntityTypes::Enemy && impactor->Tag != Entity::EntityTypes::BulletFloaters && impactor->Tag != Entity::EntityTypes::BulletSkulls)
            {
                this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));
                if (isLeftOrRightKeyPressed)
                {
                    this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
                }
                else
                {
                    this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
                }
            }
        }
        return;

    default:
        break;
    }
}

PlayerState::StateName PlayerInjuringFallState::GetState()
{
    return PlayerState::InjuringFall;
}