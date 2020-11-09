#include "PlayerRunningOverheadState.h"
#include "PlayerStandingOverheadState.h"

PlayerRunningOverheadState::PlayerRunningOverheadState(PlayerData* playerData)
{
    this->mPlayerData = playerData;

    acceleratorX = 28.0f;
}

PlayerRunningOverheadState::PlayerRunningOverheadState()
{
    
}


PlayerRunningOverheadState::~PlayerRunningOverheadState()
{
}

void PlayerRunningOverheadState::Update(float dt)
{

}

void PlayerRunningOverheadState::HandleKeyboard(std::map<int, bool> keys)
{
    if (keys[VK_RIGHT])
    {
        if (mPlayerData->player->allowMoveRight)
        {
            mPlayerData->player->SetReverse(false);
            this->mPlayerData->player->SetVx(140);
            if (keys[VK_UP] && mPlayerData->player->allowMoveUp)
            {
                this->mPlayerData->player->SetVy(-140);
            }
            else if (keys[VK_DOWN] && mPlayerData->player->allowMoveDown)
            {
                this->mPlayerData->player->SetVy(140);
            }
            else this->mPlayerData->player->SetVy(0);
        }
    }
    else if (keys[VK_LEFT])
    {
        if (mPlayerData->player->allowMoveLeft)
        {
            mPlayerData->player->SetReverse(true);
            this->mPlayerData->player->SetVx(-140);
            if (keys[VK_UP] && mPlayerData->player->allowMoveUp)
            {
                this->mPlayerData->player->SetVy(-140);
            }
            else if (keys[VK_DOWN] && mPlayerData->player->allowMoveDown)
            {
                this->mPlayerData->player->SetVy(140);
            }
            else this->mPlayerData->player->SetVy(0);
        }
    }
    else
    {
        this->mPlayerData->player->SetState(new PlayerStandingOverheadState(this->mPlayerData));
        return;
    }
}

void PlayerRunningOverheadState::OnCollision(Entity* impactor, Entity::SideCollisions side, Entity::CollisionReturn data)
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

            this->mPlayerData->player->SetState(new PlayerStandingOverheadState(this->mPlayerData));
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
            this->mPlayerData->player->SetState(new PlayerStandingOverheadState(this->mPlayerData));
        }
        return;
    }

    case Entity::Top:
        this->mPlayerData->player->AddPosition(0, (data.RegionCollision.bottom - data.RegionCollision.top));

        this->mPlayerData->player->SetVy(0);

        return;
        break;

    case Entity::Bottom: 
    case Entity::BottomLeft: 
    case Entity::BottomRight:
    {
        this->mPlayerData->player->AddPosition(0, -(data.RegionCollision.bottom - data.RegionCollision.top));

        this->mPlayerData->player->SetVy(0);

        return;
    }
    }
}

PlayerState::StateName PlayerRunningOverheadState::GetState()
{
    return PlayerState::RunningOverhead;
}