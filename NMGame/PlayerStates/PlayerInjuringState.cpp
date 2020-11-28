#include "PlayerInjuringState.h"
#include "../Player.h"
#include "PlayerFallingState.h"
#include "PlayerAttackingState.h"
#include "PlayerAttacking90State.h"
#include "PlayerJumpingState.h"
#include "PlayerRunningState.h"
#include "PlayerStandingState.h"
#include "PlayerInjuringJumpState.h"
#include "../GameDefines.h"
#include "../GameSound.h"

PlayerInjuringState::PlayerInjuringState(PlayerData* playerData)
{
    this->mPlayerData = playerData;
    this->mPlayerData->player->SetVx(0);
    this->mPlayerData->player->SetVy(0);
    this->mTimeExist = 1.0f;
    this->mCurrentTime = 0;
    GameSound::GetInstance()->Play("Assets/Sounds/injuring.mp3");
}


PlayerInjuringState::~PlayerInjuringState()
{
}

void PlayerInjuringState::Update(float dt)
{
    if (mCurrentTime >= mTimeExist)
    {
        this->mPlayerData->player->SetState(new PlayerStandingState(this->mPlayerData));
        return;
    }
    else
    {
        mCurrentTime += dt;
    }
}

void PlayerInjuringState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        //this->mPlayerData->player->SetState(new PlayerRunningState(this->mPlayerData));
        if (this->mPlayerData->player->allowMoveRight)
        {
            mPlayerData->player->SetReverse(false);
            this->mPlayerData->player->SetVx(180);
        }
        return;
    }
    else if (keys[VK_LEFT])
    {
        if (this->mPlayerData->player->allowMoveLeft)
        {
            mPlayerData->player->SetReverse(true);
            this->mPlayerData->player->SetVx(-180);
        }
        return;
    }
    else
    {
        this->mPlayerData->player->SetVx(0);
    }
}

void PlayerInjuringState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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
        }
        return;
    }
    }
}

PlayerState::StateName PlayerInjuringState::GetState()
{
    return PlayerState::Injuring;
}