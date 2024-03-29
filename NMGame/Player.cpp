#include "Player.h"
#include "PlayerStates/PlayerRunningState.h"
#include "PlayerStates/PlayerJumpingState.h"
#include "PlayerStates/PlayerStandingState.h"
#include "PlayerStates/PlayerFallingState.h"
#include "PlayerStates/PlayerAttackingState.h"
#include "PlayerStates/PlayerAttack90RunningState.h"
#include "PlayerStates/PlayerAttacking90State.h"
#include <string>

Player::Player()
{
    mAnimationRunning = new Animation("Assets/sophiaRunning.png", 4, 1, 4, 0.08f);
    mAnimationStanding = new Animation("Assets/sophiaIdle.png", 2, 1, 2, 0.25f);
    mAnimationJumping = new Animation("Assets/sophiaJumping.png", 4, 1, 4, 0.6f);
    mAnimationAttacking = new Animation("Assets/sophiaAttack45.png", 1, 1, 1, 0);
    mAnimationFalling = new Animation("Assets/sophiaFalling.png", 4, 1, 4, 0.4f);
    mAnimationAttackRunning = new Animation("Assets/sophiaRunAttack45.png", 4, 1, 4, 0.08f);
    mAnimationAttacking90 = new Animation("Assets/sophiaAttack90.png", 1, 1, 1, 0);
    mAnimationAttack90Running = new Animation("Assets/sophiaRunAttack90.png", 4, 1, 4, 0.08f);
    mSophia = nullptr;
    isShowJason = false;

    this->mPlayerData = new PlayerData();
    this->mPlayerData->player = this;
    this->vx = 0;
    this->vy = 0;
    this->SetState(new PlayerFallingState(this->mPlayerData));

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
                    mAnimationJumping = new Animation("Assets/sophiaJumping.png", 4, 1, 4, 0.6f);
                    mAnimationAttacking = new Animation("Assets/sophiaAttack45.png", 1, 1, 1, 0);
                    mAnimationFalling = new Animation("Assets/sophiaFalling.png", 4, 1, 4, 0.08f);
                    mAnimationAttackRunning = new Animation("Assets/sophiaRunAttack45.png", 4, 1, 4, 0.08f);
                    mAnimationAttacking90 = new Animation("Assets/sophiaAttack90.png", 1, 1, 1, 0);
                    mAnimationAttack90Running = new Animation("Assets/sophiaRunAttack90.png", 4, 1, 4, 0.08f);
                    mCurrentAnimation = mAnimationStanding;
                    isShowJason = false;
                }
            }
            else
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
                mCurrentAnimation = mAnimationStanding;
                this->AddVy(-240);
                isShowJason = true;
            }
        }
    }
    else if (key == 0x4A)
    {
        if (allowShoot)
        {
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
}

void Player::OnKeyUp(int key)
{
    if (key == VK_SPACE)
        allowJump = true;
    if (key == 0x4A)
        allowShoot = true;
}

void Player::SetReverse(bool flag)
{
    mCurrentReverse = flag;
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
        mPowerView->Draw(D3DXVECTOR3(mCamera->GetPosition().x - 200, mCamera->GetPosition().y + 150, 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
        for (int i = mPower - 1; i >= 0; i--)
        {
            mPowerItems.at(i)->Draw(D3DXVECTOR3(mCamera->GetPosition().x - 200, mCamera->GetPosition().y + 97 + 10 * (7 - i), 0), sourceRect, scale, trans, angle, rotationCenter, colorKey);
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
    if (mCurrentState != PlayerState::Jumping && mCurrentState != PlayerState::Falling)
    {
        this->SetState(new PlayerFallingState(this->mPlayerData));
    }
}

void Player::OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side)
{
    this->mPlayerData->state->OnCollision(impactor, side, data);
}