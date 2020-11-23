#include "Player.h"
#include "PlayerStates/PlayerRunningState.h"
#include "PlayerStates/PlayerJumpingState.h"
#include "PlayerStates/PlayerStandingState.h"
#include "PlayerStates/PlayerFallingState.h"
#include "PlayerStates/PlayerAttackingState.h"
#include "PlayerStates/PlayerAttack90RunningState.h"
#include "PlayerStates/PlayerAttacking90State.h"
#include "PlayerStates/PlayerInjuringState.h"
#include "PlayerStates/PlayerInjuringJumpState.h"
#include "PlayerStates/PlayerInjuringDownOverheadState.h"
#include "PlayerStates/PlayerInjuringOverheadState.h"
#include "PlayerStates/PlayerInjuringUpOverheadState.h"
#include "MapObjects/ThunderBullet.h"
#include "MapObjects/RocketBullet.h"
#include "MapObjects/MissileBullet.h"
#include <string>
#include "GameSound.h"

Player::Player()
{
    mAnimationRunning = new Animation("Assets/sophiaRunning.png", 4, 1, 4, 0.08f);
    mAnimationStanding = new Animation("Assets/sophiaIdle.png", 2, 1, 2, 0.25f);
    mAnimationJumping = new Animation("Assets/sophiaJumping.png", 4, 4, 4, 0.06f);
    mAnimationAttacking = new Animation("Assets/sophiaAttack45.png", 1, 1, 1, 0);
    mAnimationFalling = new Animation("Assets/sophiaFalling.png", 4, 4, 4, 0.06f);
    mAnimationAttackRunning = new Animation("Assets/sophiaRunAttack45.png", 4, 1, 4, 0.08f);
    mAnimationAttacking90 = new Animation("Assets/sophiaAttack90.png", 1, 1, 1, 0);
    mAnimationAttack90Running = new Animation("Assets/sophiaRunAttack90.png", 4, 1, 4, 0.08f);
    mAnimationInjuring = new Animation("Assets/sophiaInjuring.png", 2, 1, 2, 0.02f);
    mAnimationInjuringJump = new Animation("Assets/sophiaInjuring.png", 2, 1, 2, 0.02f);
    mAnimationClimbing = new Animation("Assets/climb.png", 2, 1, 2, 0.25f);
    mAnimationFlipping = new Animation("Assets/sophiaFlipping.png", 4, 1, 4, 0.08f);
    mSophia = nullptr;
    isShowJason = false;

    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerStandingState(this->mPlayerData));
    skill = 2;

    allowJump = true;
    allowShoot = true;
    mPower = 8;
    isOnLadder = false;
    isGoingLadder = false;
    for (int i = 0; i < 8; i++)
    {
        mPowerItems.push_back(new Sprite("Assets/powerItem.png"));
    }
    mPowerView = new Sprite("Assets/power.png");

    Tag = EntityTypes::Player;
}

Player::~Player()
{
}

void Player::Update(float dt)
{
    mCurrentAnimation->Update(dt);

    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->Update(dt);
    }

    for (int i = 0; i < mBullets.size(); i++)
    {
        if (mBullets[i] && mBullets[i]->mIsValid)
        {
            mBullets[i]->Update(dt);
        }
        else
        {
            delete mBullets[i];
            mBullets.erase(mBullets.begin() + i);
        }
    }

    Entity::Update(dt);
}

void Player::HandleKeyboard(std::map<int, bool> keys)
{
    if (this->mPlayerData->state)
    {
        this->mPlayerData->state->HandleKeyboard(keys);
    }
}

void Player::SetCamera(Camera* camera)
{
    this->mCamera = camera;
}

void Player::OnKeyPressed(int key)
{
    if (key == VK_SPACE)
    {
        if (allowJump)
        {
            if (mCurrentState == PlayerState::Running || mCurrentState == PlayerState::Standing)
            {
                this->SetState(new PlayerJumpingState(this->mPlayerData));
            }
            if (mCurrentState == PlayerState::Injuring)
            {
                this->SetState(new PlayerInjuringJumpState(this->mPlayerData));
            }
            allowJump = false;
        }
    }
    else if (key == 0x49)
    {
        if (mCurrentState == PlayerState::Standing)
        {
            if (isShowJason)
            {
                if (abs(this->GetPosition().x - mSophia->GetPosition().x) < mSophia->GetWidth() / 2 && abs(this->GetPosition().y - mSophia->GetPosition().y) < mSophia->GetHeight() / 2)
                {
                    this->SetPosition(mSophia->GetPosition());
                    mSophia = nullptr;
                    mAnimationRunning = new Animation("Assets/sophiaRunning.png", 4, 1, 4, 0.08f);
                    mAnimationStanding = new Animation("Assets/sophiaIdle.png", 2, 1, 2, 0.25f);
                    mAnimationJumping = new Animation("Assets/sophiaJumping.png", 4, 4, 4, 0.06f);
                    mAnimationAttacking = new Animation("Assets/sophiaAttack45.png", 1, 1, 1, 0);
                    mAnimationFalling = new Animation("Assets/sophiaFalling.png", 4, 4, 4, 0.06f);
                    mAnimationAttackRunning = new Animation("Assets/sophiaRunAttack45.png", 4, 1, 4, 0.08f);
                    mAnimationAttacking90 = new Animation("Assets/sophiaAttack90.png", 1, 1, 1, 0);
                    mAnimationAttack90Running = new Animation("Assets/sophiaRunAttack90.png", 4, 1, 4, 0.08f);
                    mAnimationInjuring = new Animation("Assets/sophiaInjuring.png", 2, 1, 2, 0.02f);
                    mAnimationInjuringJump = new Animation("Assets/sophiaInjuring.png", 2, 1, 2, 0.02f);
                    mAnimationFlipping = new Animation("Assets/sophiaFlipping.png", 4, 1, 4, 0.08f);
                    mCurrentAnimation = mAnimationStanding;
                    isShowJason = false;
                }
            }
            else
            {
                showJason();
            }
        }
    }
    else if (key == 0x4A)
    {
        if (allowShoot)
        {
            GameSound::GetInstance()->Play("Assets/Sounds/shoot.mp3");
            if (!mCurrentReverse)
            {
                if (mCurrentState == PlayerState::Attacking90 || mCurrentState == PlayerState::Attack90Running)
                {
                    this->mPlayerData->player->mBullets.push_back(new Bullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y - 10 - 24, 0), 90));
                }
                else if (mCurrentState == PlayerState::Attacking || mCurrentState == PlayerState::AttackRunning)
                {
                    this->mPlayerData->player->mBullets.push_back(new Bullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x + 32, mPlayerData->player->GetPosition().y - 8 - 24, 0), 45));
                }
                else
                {
                    this->mPlayerData->player->mBullets.push_back(new Bullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x + 24, mPlayerData->player->GetPosition().y - 12, 0), 0));
                }
            }
            else
            {
                if (mCurrentState == PlayerState::Attacking90 || mCurrentState == PlayerState::Attack90Running)
                {
                    this->mPlayerData->player->mBullets.push_back(new Bullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y - 10 - 24, 0), 90));
                }
                else if (mCurrentState == PlayerState::Attacking || mCurrentState == PlayerState::AttackRunning)
                {
                    this->mPlayerData->player->mBullets.push_back(new Bullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x - 32, mPlayerData->player->GetPosition().y - 8 - 24, 0), 135));
                }
                else
                {
                    this->mPlayerData->player->mBullets.push_back(new Bullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x - 24, mPlayerData->player->GetPosition().y - 12, 0), 180));
                }
            }
            allowShoot = false;
        }
    }
    else if (key == 0x58)
    {
        if (allowShoot && !isShowJason)
        {
            if ((skill == 1 && missleBulletCount > 0) || (skill == 2 && thunderBulletCount > 0) || (skill == 3 && rocketBulletCount > 0))
            {
                GameSound::GetInstance()->Play("Assets/Sounds/shoot.mp3");
                switch (skill)
                {
                case 1:
                    Bullet * tmp;
                    if (!mCurrentReverse)
                    {
                        tmp = new MissileBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x + 50, mPlayerData->player->GetPosition().y, 0), 0);
                    }
                    else
                    {
                        tmp = new MissileBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x - 50, mPlayerData->player->GetPosition().y, 0), 180);
                    }
                    tmp->SetMission(mEnemyPos);
                    this->mPlayerData->player->mBullets.push_back(tmp);
                    missleBulletCount--;
                    break;
                case 2:
                    this->mPlayerData->player->mBullets.push_back(new ThunderBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x, mPlayerData->player->GetPosition().y + 90, 0)));
                    thunderBulletCount--;
                    break;
                case 3:
                    if (!mCurrentReverse)
                    {
                        this->mPlayerData->player->mBullets.push_back(new RocketBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x + 50, mPlayerData->player->GetPosition().y, 0), 0, 1));
                        this->mPlayerData->player->mBullets.push_back(new RocketBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x + 50, mPlayerData->player->GetPosition().y, 0), 0, 2));
                        this->mPlayerData->player->mBullets.push_back(new RocketBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x + 50, mPlayerData->player->GetPosition().y, 0), 0, 3));
                    }
                    else
                    {
                        this->mPlayerData->player->mBullets.push_back(new RocketBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x - 50, mPlayerData->player->GetPosition().y, 0), 180, 1));
                        this->mPlayerData->player->mBullets.push_back(new RocketBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x - 50, mPlayerData->player->GetPosition().y, 0), 180, 2));
                        this->mPlayerData->player->mBullets.push_back(new RocketBullet(D3DXVECTOR3(mPlayerData->player->GetPosition().x - 50, mPlayerData->player->GetPosition().y, 0), 180, 3));
                    }
                    rocketBulletCount--;
                    break;
                default:
                    break;
                }
                allowShoot = false;
            }
        }
    }
}

void Player::showJason()
{
    mSophia = new Sprite("Assets/sophia.png");
    mSophia->FlipVertical(mCurrentReverse);
    mSophia->SetPosition(this->GetPosition());
    mAnimationRunning = new Animation("Assets/run.png", 3, 1, 3, 0.08f);
    mAnimationStanding = new Animation("Assets/idle.png", 1, 1, 1, 0);
    mAnimationJumping = new Animation("Assets/idle.png", 1, 1, 1, 0);
    mAnimationAttacking = new Animation("Assets/idle.png", 1, 1, 1, 0);
    mAnimationFalling = new Animation("Assets/idle.png", 1, 1, 1, 0);
    mAnimationAttackRunning = new Animation("Assets/run.png", 3, 1, 3, 0.08f);
    mAnimationAttacking90 = new Animation("Assets/idle.png", 1, 1, 1, 0);
    mAnimationAttack90Running = new Animation("Assets/run.png", 3, 1, 3, 0.08f);
    mAnimationInjuring = new Animation("Assets/injuring.png", 2, 1, 2, 0.02f);
    mAnimationInjuringJump = new Animation("Assets/injuring.png", 2, 1, 2, 0.02f);
    mCurrentAnimation = mAnimationStanding;
    this->AddVy(-240);
    isShowJason = true;
}

void Player::OnKeyUp(int key)
{
    if (key == VK_SPACE)
        allowJump = true;
    if (key == 0x4A || key == 0x58)
        allowShoot = true;
}

void Player::SetReverse(bool flag)
{
    mCurrentReverse = flag;
}

bool Player::GetReverse()
{
    return mCurrentReverse;
}

void Player::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mCurrentAnimation->FlipVertical(mCurrentReverse);
    mCurrentAnimation->SetPosition(this->GetPosition());

    if (mCamera)
    {
        D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
            GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

        if (mSophia)
            mSophia->Draw(mSophia->GetPosition(), sourceRect, scale, trans, angle, rotationCenter, colorKey);

        mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
        // vien dan
        for (int i = 0; i < mBullets.size(); i++)
            mBullets[i]->Draw(mBullets[i]->GetPosition(), sourceRect, scale, trans, angle, rotationCenter, colorKey);
        mPowerView->Draw(D3DXVECTOR3(mCamera->GetPosition().x - 198, mCamera->GetPosition().y + 112, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
        for (int i = mPower - 1; i >= 0; i--)
        {
            mPowerItems.at(i)->Draw(D3DXVECTOR3(mCamera->GetPosition().x - 200, mCamera->GetPosition().y + 97 + 8 * (7 - i), 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
        }
    }
    else
    {
        if (mSophia)
            mSophia->Draw(D3DXVECTOR3(posX, posY, 0));
        mCurrentAnimation->Draw(D3DXVECTOR3(posX, posY, 0));
        // vien dan
        for (int i = 0; i < mBullets.size(); i++)
            mBullets[i]->Draw(mBullets[i]->GetPosition());
    }
}

void Player::SetState(PlayerState* newState)
{
    allowMoveLeft = true;
    allowMoveRight = true;
    allowMoveUp = true;
    allowMoveDown = true;
    delete this->mPlayerData->state;

    this->mPlayerData->state = newState;

    this->changeAnimation(newState->GetState());

    mCurrentState = newState->GetState();
}

RECT Player::GetBound()
{
    RECT rect;
    rect.left = this->posX - mCurrentAnimation->GetWidth() / 2;
    rect.right = rect.left + mCurrentAnimation->GetWidth();
    rect.top = this->posY - mCurrentAnimation->GetHeight() / 2;
    rect.bottom = rect.top + mCurrentAnimation->GetHeight();
    return rect;
}

void Player::changeAnimation(PlayerState::StateName state)
{
    switch (state)
    {
    case PlayerState::Running:
        mCurrentAnimation = mAnimationRunning;
        break;

    case PlayerState::Standing:
        mCurrentAnimation = mAnimationStanding;
        break;

    case PlayerState::Falling:
        mCurrentAnimation = mAnimationFalling;
        break;

    case PlayerState::Jumping:
        mCurrentAnimation = mAnimationJumping;
        break;
    case PlayerState::Attacking:
        mCurrentAnimation = mAnimationAttacking;
        break;
    case PlayerState::AttackRunning:
        mCurrentAnimation = mAnimationAttackRunning;
        break;
    case PlayerState::Attacking90:
        mCurrentAnimation = mAnimationAttacking90;
        break;
    case PlayerState::Attack90Running:
        mCurrentAnimation = mAnimationAttack90Running;
        break;
    case PlayerState::Injuring:
        mCurrentAnimation = mAnimationInjuring;
        break;
    case PlayerState::Climbing:
        mCurrentAnimation = mAnimationClimbing;
        break;
    case PlayerState::StandingOverhead:
        mCurrentAnimation = mAnimationStandingOverhead;
        break;
    case PlayerState::RunningOverhead:
        mCurrentAnimation = mAnimationRunningOverhead;
        break;
    case PlayerState::RunningUpOverhead:
        mCurrentAnimation = mAnimationRunningUpOverhead;
        break;
    case PlayerState::RunningDownOverhead:
        mCurrentAnimation = mAnimationRunningDownOverhead;
        break;
    case PlayerState::StandingUpOverhead:
        mCurrentAnimation = mAnimationStandingUpOverhead;
        break;
    case PlayerState::StandingDownOverhead:
        mCurrentAnimation = mAnimationStandingDownOverhead;
        break;
    case PlayerState::InjuringOverhead:
        mCurrentAnimation = mAnimationInjuringOverhead;
        break;
    case PlayerState::InjuringUpOverhead:
        mCurrentAnimation = mAnimationInjuringUpOverhead;
        break;
    case PlayerState::InjuringDownOverhead:
        mCurrentAnimation = mAnimationInjuringDownOverhead;
        break;
    case PlayerState::InjuringJump:
        mCurrentAnimation = mAnimationInjuringJump;
        break;
    case PlayerState::Flipping:
        delete mAnimationFlipping;
        mAnimationFlipping = new Animation("Assets/sophiaFlipping.png", 4, 1, 4, 0.1f);
        mCurrentAnimation = mAnimationFlipping;
        break;
    }

    this->SetPosition(this->GetPosition().x, this->GetPosition().y - (mCurrentAnimation->GetHeight() - this->GetHeight()) / 2);
    this->width = mCurrentAnimation->GetWidth();
    this->height = mCurrentAnimation->GetHeight();
}

Player::MoveDirection Player::getMoveDirection()
{
    if (this->vx > 0)
    {
        return MoveDirection::MoveToRight;
    }
    else if (this->vx < 0)
    {
        return MoveDirection::MoveToLeft;
    }

    return MoveDirection::None;
}

PlayerState::StateName Player::getState()
{
    return mCurrentState;
}

PlayerData* Player::getPlayerData()
{
    return mPlayerData;
}

void Player::OnNoCollisionWithBottom()
{
    if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling && mCurrentState != PlayerState::Climbing && !isGoingLadder && mCurrentState != PlayerState::InjuringJump)
    {
        this->SetState(new PlayerFallingState(this->mPlayerData));
    }
}

void Player::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    if (impactor->Tag == EntityTypes::Enemy || impactor->Tag == EntityTypes::BulletSkulls || impactor->Tag == EntityTypes::BulletFloaters || impactor->Tag == EntityTypes::Dangers || impactor->Tag == EntityTypes::BulletCannons)
    {
        if (this->mCurrentState == PlayerState::RunningOverhead || mCurrentState == PlayerState::StandingOverhead || mCurrentState == PlayerState::InjuringOverhead)
        {
            this->SetState(new PlayerInjuringOverheadState(mPlayerData));
        }
        else if (mCurrentState == PlayerState::RunningUpOverhead || mCurrentState == PlayerState::StandingUpOverhead || mCurrentState == PlayerState::InjuringUpOverhead)
        {
            this->SetState(new PlayerInjuringUpOverheadState(mPlayerData));
        }
        else if (mCurrentState == PlayerState::RunningDownOverhead || mCurrentState == PlayerState::StandingDownOverhead || mCurrentState == PlayerState::InjuringDownOverhead)
        {
            this->SetState(new PlayerInjuringDownOverheadState(mPlayerData));
        }
        else
        {
            this->SetState(new PlayerInjuringState(this->mPlayerData));
        }
    }
    this->mPlayerData->state->OnCollision(impactor, side, data);
}

void Player::SetEnemyPos(vector<D3DXVECTOR3> mEnemyPos)
{
    this->mEnemyPos.clear();
    for (int i = 0; i < mEnemyPos.size(); i++)
    {
        this->mEnemyPos.push_back(mEnemyPos.at(i));
    }
}