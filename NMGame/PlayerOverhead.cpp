#include "PlayerOverhead.h"
#include "PlayerStates/PlayerStandingOverheadState.h"
#include "MapObjects/BulletOverhead.h"

PlayerOverhead::PlayerOverhead()
{
    mAnimationRunningOverhead = new Animation("Assets/goRun.png", 3, 1, 3, 0.25f);
    mAnimationRunningDownOverhead = new Animation("Assets/goDown.png", 3, 1, 3, 0.25f);
    mAnimationRunningUpOverhead = new Animation("Assets/goUp.png", 3, 1, 3, 0.25f);
    mAnimationStandingOverhead = new Animation("Assets/standing.png", 1, 1, 1, 0.25f);
    mAnimationStandingUpOverhead = new Animation("Assets/standingUp.png", 1, 1, 1, 0.25f);
    mAnimationStandingDownOverhead = new Animation("Assets/standingDown.png", 1, 1, 1, 0.25f);
    mAnimationInjuringOverhead = new Animation("Assets/injuringOverhead.png", 2, 1, 2, 0.02f);
    mAnimationInjuringUpOverhead = new Animation("Assets/injuringUpOverhead.png", 2, 1, 2, 0.02f);
    mAnimationInjuringDownOverhead = new Animation("Assets/injuringDownOverhead.png", 2, 1, 2, 0.02f);

    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerStandingOverheadState(this->mPlayerData));

    allowJump = true;
    allowShoot = true;
    mPower = 8;
    for (int i = 0; i < 8; i++)
    {
        mPowerItems.push_back(new Sprite("Assets/powerItem.png"));
    }
    mPowerView = new Sprite("Assets/power.png");

    Tag = EntityTypes::Player;
}

PlayerOverhead::~PlayerOverhead()
{

}

void PlayerOverhead::OnKeyUp(int key)
{
    if (key == 0x4A)
        allowShoot = true;
}

void PlayerOverhead::OnKeyPressed(int key)
{
    if (key == 0x4A)
    {
        if (allowShoot)
        {
            if (mCurrentState == PlayerState::RunningUpOverhead || mCurrentState == PlayerState::StandingUpOverhead || mCurrentState == PlayerState::InjuringUpOverhead)
            {
                this->mPlayerData->player->mBullets.push_back(new BulletOverhead(D3DXVECTOR3(mPlayerData->player->GetPosition().x - 10, mPlayerData->player->GetPosition().y - 32, 0), 90));
            }
            else if (mCurrentState == PlayerState::RunningDownOverhead || mCurrentState == PlayerState::StandingDownOverhead || mCurrentState == PlayerState::InjuringDownOverhead)
            {
                this->mPlayerData->player->mBullets.push_back(new BulletOverhead(D3DXVECTOR3(mPlayerData->player->GetPosition().x + 10, mPlayerData->player->GetPosition().y + 24, 0), 270));
            }
            else
            {
                if (!mCurrentReverse)
                {
                    this->mPlayerData->player->mBullets.push_back(new BulletOverhead(D3DXVECTOR3(mPlayerData->player->GetPosition().x + 24, mPlayerData->player->GetPosition().y, 0), 0));
                }
                else
                {
                    this->mPlayerData->player->mBullets.push_back(new BulletOverhead(D3DXVECTOR3(mPlayerData->player->GetPosition().x - 24, mPlayerData->player->GetPosition().y, 0), 180));
                }
            }
            allowShoot = false;
        }
    }
}