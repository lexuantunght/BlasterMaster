#pragma once
#include <d3d9.h>
#include <d3dx9.h>
#include "Animation.h"
#include "Sprite.h"
#include "GameGlobal.h"
#include "Camera.h"
#include "Entity.h"
#include "PlayerState.h"
#include "PlayerData.h"
#include "PlayerStates/PlayerJumpingState.h"
#include "PlayerStates/PlayerRunningState.h"
#include "PlayerStates/PlayerFallingState.h"
#include "PlayerStates/PlayerStandingState.h"
#include "MapObjects/Bullet.h"

class Player : public Entity
{
public:
    Player();
    ~Player();

    enum MoveDirection
    {
        MoveToLeft, //chay tu phai sang trai
        MoveToRight, //chay tu trai sang phai
        None //dung im
    };

    void SetCamera(Camera* camera);

    void Update(float dt);

    void Draw(D3DXVECTOR3 position = D3DXVECTOR3(), RECT sourceRect = RECT(), D3DXVECTOR2 scale = D3DXVECTOR2(), D3DXVECTOR2 transform = D3DXVECTOR2(), float angle = 0, D3DXVECTOR2 rotationCenter = D3DXVECTOR2(), D3DXCOLOR colorKey = D3DCOLOR_XRGB(255, 255, 255));

    void SetState(PlayerState* newState);

    MoveDirection getMoveDirection();

    void OnCollision(Entity* impactor, Entity::CollisionReturn data, Entity::SideCollisions side);

    void OnNoCollisionWithBottom();

    RECT GetBound();

    PlayerState::StateName getState();
    PlayerData* getPlayerData();
    //xu ly input
    //gom 256 key tuong ung true = dang dc nhan, false = khong dc nhan
    void HandleKeyboard(std::map<int, bool> keys);

    virtual void OnKeyPressed(int key);

    virtual void OnKeyUp(int key);

    //true thi se lat nguoc anh theo truc y
    void SetReverse(bool flag);
    bool GetReverse();

    void showJason();

    bool allowMoveRight;
    bool allowMoveLeft;
    bool allowMoveUp;
    bool allowMoveDown;

    vector<Bullet*> mBullets;
    int mPower;
    bool isShowJason;
    bool isOnLadder;
    bool isGoingLadder;
    Sprite* mSophia;
protected:
    PlayerData* mPlayerData;

    Camera* mCamera;

    Animation* mCurrentAnimation,
        * mAnimationRunning,
        * mAnimationFalling,
        * mAnimationStanding,
        * mAnimationFlipping,
        * mAnimationAttacking,
        * mAnimationAttackRunning,
        * mAnimationAttacking90,
        * mAnimationAttack90Running,
        * mAnimationJumping,
        * mAnimationInjuring,
        * mAnimationInjuringJump,
        * mAnimationInjuringDownOverhead,
        * mAnimationInjuringUpOverhead,
        * mAnimationInjuringOverhead,
        * mAnimationStandingOverhead,
        * mAnimationStandingUpOverhead,
        * mAnimationStandingDownOverhead,
        * mAnimationRunningOverhead,
        * mAnimationRunningUpOverhead,
        * mAnimationRunningDownOverhead,
        * mAnimationClimbing;

    Sprite* mPowerView;
    vector<Sprite*> mPowerItems;

    void changeAnimation(PlayerState::StateName state);

    PlayerState::StateName mCurrentState;

    //chi cho phep jump khi nhan nhim space, muon nhay lai phai tha phim space roi nhan lai
    bool allowJump, mCurrentReverse;
    bool allowShoot;
};