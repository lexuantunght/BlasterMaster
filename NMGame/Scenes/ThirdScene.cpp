#include "ThirdScene.h"
#include "../PlayerOverhead.h"
#include "../SceneManager.h"
#include "../PlayerStates/PlayerRunningOverheadState.h"
#include "../PlayerStates/PlayerStandingOverheadState.h"
#include "../PlayerStates/PlayerRunningUpOverheadState.h"
#include "../PlayerStates/PlayerRunningDownOverheadState.h"
#include "../PlayerStates/PlayerStandingDownOverheadState.h"
#include "../PlayerStates/PlayerStandingUpOverheadState.h"
#include "../MapObjects/Teleporter.h"
#include "../MapObjects/Cannon.h"
#include "../MapObjects/BulletCannon.h"
#include "../MapObjects/Eyeball.h"
#include "../MapObjects/BulletEyeball.h"
#include "../MapObjects/Boss.h"
#include "FirstScene.h"
#include "../GameSound.h"
#include <string>
#include <fstream>
ThirdScene::ThirdScene()
{
	LoadContent();
}

ThirdScene::ThirdScene(D3DXVECTOR3 oldPos, bool currReverse)
{
	this->currReverse = currReverse;
	this->oldPos = oldPos;
	LoadContent();
}

ThirdScene::~ThirdScene()
{
    delete mPlayer;
    delete mMap;
    delete bossBackground;
    delete bossStage;
}

void ThirdScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x1E1E1E;
    isReplace = false;

    mMap = new Map("Assets/overworld2.tmx");
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - GameGlobal::GetHeight() / 4);
    mMap->SetCamera(mCamera);

    LoadEnemies("Assets/enemies_overworld2.txt");
    LoadRocks("Assets/mapObjects.txt");

    mItemCollections.push_back(new ItemCollection(D3DXVECTOR3(1360, 3372, 0), 1));

    //get bound submap
    mListMapBound = new RECT[21];
    LoadMapBound("Assets/map_bounds_overworld2.txt");
    mCurrentMapBound = mListMapBound[0];

    mPlayer = new PlayerOverhead();
    mPlayer->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - GameGlobal::GetHeight() / 4);
    //mPlayer->SetPosition(1700, 1800);
    mPlayer->SetCamera(mCamera);
    bossBackground = new Sprite("Assets/Boss/bossBG.png");
    bossStage = new Animation("Assets/Boss/bossStage.png", 2, 1, 2, 0.15f);
    mIsBossStage = false;
    mIsLoadedBossStage = false;
    mIsKilledBoss = false;
    mCountPreBoss = 0;
}

const vector<string> explode2(const string& s, const char& c)
{
    string buff{ "" };
    vector<string> v;

    for (auto n : s)
    {
        if (n != c) buff += n; else
            if (n == c && buff != "") { v.push_back(buff); buff = ""; }
    }
    if (buff != "") v.push_back(buff);

    return v;
}

void ThirdScene::LoadMapBound(const char* path)
{
    //left->top->bottom->right
    fstream f;
    f.open(path, std::ios::in);
    int i = 0;
    while (!f.eof())
    {
        string line;
        std::getline(f, line);
        vector<string> info = { explode2(line, ' ') };
        mListMapBound[i].left = stoi(info[0]);
        mListMapBound[i].top = stoi(info[1]);
        mListMapBound[i].bottom = stoi(info[2]);
        mListMapBound[i].right = stoi(info[3]);
        i++;
    }
    f.close();
}

void ThirdScene::LoadEnemies(const char* path)
{
    // teleporter = 1, cannon = 2, eyeball = 3, boss = 4
    fstream f;
    f.open(path, std::ios::in);
    while (!f.eof())
    {
        string line;
        std::getline(f, line);
        vector<string> info = { explode2(line, ' ') };
        if (info[0] == "1")
        {
            mEnemies.push_back(new Teleporter(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3]), stoi(info[4])));
        }
        else if (info[0] == "2")
        {
            mEnemies.push_back(new Cannon(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3]), stoi(info[4])));
        }
        else if (info[0] == "3")
        {
            mEnemies.push_back(new Eyeball(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3]), stoi(info[4])));
        }
        else if (info[0] == "4")
        {
            mEnemies.push_back(new Boss(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3]), stoi(info[4])));
            mEnemies[mEnemies.size() - 1]->mIsActive = false;
        }
    }
    f.close();
}

void ThirdScene::LoadRocks(const char* path)
{
    fstream f;
    f.open(path, std::ios::in);
    while (!f.eof())
    {
        string line;
        std::getline(f, line);
        vector<string> info = { explode2(line, ' ') };
        if (info[0] == "1")
        {
            mRocks.push_back(new Rock(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3])));
        }
    }
    f.close();
}

void ThirdScene::Update(float dt)
{
    //game process
    if (!mIsPassGateRight && !mIsPassGateLeft && !mIsPassGateTop && !mIsPassGateBottom) checkCollision();
    if (isReplace) return;
    mMap->Update(dt);
    if (!mIsPassGateRight && !mIsPassGateLeft && !mIsPassGateTop && !mIsPassGateBottom && !mIsBossStage && !mIsKilledBoss) mPlayer->HandleKeyboard(keys);
    mPlayer->Update(dt);
    if (!mIsPassGateRight && !mIsPassGateLeft && !mIsPassGateTop && !mIsPassGateBottom)
    {
        InitForEnemies(dt);
        if (!mIsLoadedBossStage)
            CheckCameraAndWorldMap();
    }
    //pass gates
    if (mIsPassGateRight) PassGateRight();
    if (mIsPassGateLeft) PassGateLeft();
    if (mIsPassGateBottom) PassGateBottom();
    if (mIsPassGateTop) PassGateTop();
    //boss stage
    if (mIsBossStage)
    {
        if (mCountPreBoss < 4.0f)
        {
            bossStage->Update(dt);
            mCountPreBoss += dt;
        }
        else
        {
            mIsBossStage = false;
            mIsLoadedBossStage = true;
            mEnemies[mEnemies.size() - 1]->mIsActive = true;
            mCountPreBoss = 0;
        }
    }
    if (mIsKilledBoss)
    {
        if (mCountPreBoss >= 5.0f)
        {
            GameSound::GetInstance()->Stop("area_clear");
            GameSound::GetInstance()->Play("Assets/Sounds/area2.mp3");
            mPlayer->SetPosition(238, 3680);
            mCurrentMapBound = mListMapBound[0];
            mIsKilledBoss = false;
        }
        else mCountPreBoss += dt;
    }
}

void ThirdScene::InitForEnemies(float dt)
{
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        if (mEnemies[i] && mEnemies[i]->GetHP() > 0)
        {
            if (mEnemies[i]->GetPosition().x > mCamera->GetBound().left - mEnemies[i]->GetWidth() / 2 && mEnemies[i]->GetPosition().x < mCamera->GetBound().right + mEnemies[i]->GetWidth() / 2
                && mEnemies[i]->GetPosition().y > mCamera->GetBound().top - mEnemies[i]->GetHeight() / 2 && mEnemies[i]->GetPosition().y < mCamera->GetBound().bottom + mEnemies[i]->GetHeight() / 2)
            {
                if (mEnemies[i]->type != Enemy::EnemyType::boss)
                    mEnemies[i]->mIsActive = true;
                if (mEnemies[i]->type == Enemy::EnemyType::eyeball && mEnemies[i]->mBullets.size() == 0)
                {
                    mEnemies[i]->mBullets.push_back(new BulletEyeball(D3DXVECTOR3(mEnemies[i]->GetPosition().x, mEnemies[i]->GetPosition().y + 10, 0)));
                    mEnemies[i]->mBullets[0]->AddVx((mPlayer->GetPosition().x - mEnemies[i]->mBullets[0]->GetPosition().x) / 3);
                    mEnemies[i]->mBullets[0]->AddVy((mPlayer->GetPosition().y - mEnemies[i]->mBullets[0]->GetPosition().y) / 3);
                }
                if (mEnemies[i]->type == Enemy::EnemyType::cannon && mEnemies[i]->mBullets.size() == 0)
                {
                    mEnemies[i]->mBullets.push_back(new BulletCannon(D3DXVECTOR3(mEnemies[i]->GetPosition().x, mEnemies[i]->GetPosition().y + 10, 0)));
                    mEnemies[i]->mBullets[mEnemies[i]->mBullets.size() - 1]->AddVy(200);
                    mEnemies[i]->mBullets.push_back(new BulletCannon(D3DXVECTOR3(mEnemies[i]->GetPosition().x, mEnemies[i]->GetPosition().y - 10, 0)));
                    mEnemies[i]->mBullets[mEnemies[i]->mBullets.size() - 1]->AddVy(-200);
                    mEnemies[i]->mBullets.push_back(new BulletCannon(D3DXVECTOR3(mEnemies[i]->GetPosition().x + 10, mEnemies[i]->GetPosition().y, 0)));
                    mEnemies[i]->mBullets[mEnemies[i]->mBullets.size() - 1]->AddVx(200);
                    mEnemies[i]->mBullets.push_back(new BulletCannon(D3DXVECTOR3(mEnemies[i]->GetPosition().x - 10, mEnemies[i]->GetPosition().y, 0)));
                    mEnemies[i]->mBullets[mEnemies[i]->mBullets.size() - 1]->AddVx(-200);
                }
            }
            else
            {
                mEnemies[i]->mIsActive = false;
                mEnemies[i]->mBullets.clear();
            }

            if (mEnemies[i]->mIsActive)
                mEnemies.at(i)->Update(dt);
        }
        else
        {
            if (mEnemies[i]->type == Enemy::EnemyType::boss)
                mIsLoadedBossStage = false;
            if (mEnemies[i]->mIsContainItem != 0)
            {
                mItemCollections.push_back(new ItemCollection(D3DXVECTOR3(mEnemies.at(i)->GetPosition().x, mEnemies.at(i)->GetPosition().y - 8, 0), mEnemies[i]->mIsContainItem));
            }
            mEnemies.erase(mEnemies.begin() + i);
        }
    }
}

void ThirdScene::CheckCameraAndWorldMap()
{
    mCamera->SetPosition(mPlayer->GetPosition());

    if (mCamera->GetBound().left < mCurrentMapBound.left)
    {
        //vi position cua camera ma chinh giua camera
        //luc nay o vi tri goc ben trai cua the gioi thuc
        mCamera->SetPosition(mCurrentMapBound.left + mCamera->GetWidth() / 2, mCamera->GetPosition().y);
    }

    if (mCamera->GetBound().right > mCurrentMapBound.right)
    {
        //luc nay cham goc ben phai cua the gioi thuc
        mCamera->SetPosition(mCurrentMapBound.right - mCamera->GetWidth() / 2,
            mCamera->GetPosition().y);
    }

    if (mCamera->GetBound().top < mCurrentMapBound.top)
    {
        //luc nay cham goc tren the gioi thuc
        mCamera->SetPosition(mCamera->GetPosition().x, mCurrentMapBound.top + mCamera->GetHeight() / 2);
    }

    if (mCamera->GetBound().bottom > mCurrentMapBound.bottom)
    {
        //luc nay cham day cua the gioi thuc
        mCamera->SetPosition(mCamera->GetPosition().x,
            mCurrentMapBound.bottom - mCamera->GetHeight() / 2);
    }
}

void ThirdScene::checkCollision()
{
    vector<Entity*> listCollision;
    vector<Entity*> listCollisionWithBullet;
    vector<Entity*> listCollisionWithEnemy;
    vector<Entity*> listCollisionWithBulletEnemy;

    mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);
    for (int i = 0; i < mPlayer->mBullets.size(); i++)
        mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithBullet, mPlayer->mBullets[i]);
    for (size_t i = 0; i < mEnemies.size(); i++)
        mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithEnemy, mEnemies[i]);

    for (size_t i = 0; i < listCollision.size(); i++)
    {
        if (listCollision[i]->Tag == Entity::EntityTypes::Dangers)
        {
            if (mPlayer->getState() == PlayerState::Injuring || mPlayer->getState() == PlayerState::InjuringOverhead
                || mPlayer->getState() == PlayerState::InjuringUpOverhead || mPlayer->getState() == PlayerState::InjuringDownOverhead)
                continue;
        }
        Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
            listCollision.at(i)->GetBound());
        //string str = std::to_string(listCollision.at(i)->GetBound().top);
        //MessageBox(0, const_cast<char*>(str.c_str()), "test", 0);
        if (r.IsCollided)
        {
            //lay phia va cham cua Entity so voi Player
            Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer, r);

            //lay phia va cham cua Player so voi Entity
            Entity::SideCollisions sideImpactor = Collision::getSideCollision(listCollision.at(i), r);

            //goi den ham xu ly collision cua Player va Entity
            mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
            listCollision.at(i)->OnCollision(mPlayer, r, sideImpactor);

            if (listCollision[i]->Tag == Entity::EntityTypes::Dangers)
            {
                if (mPlayer->getState() == PlayerState::Injuring || mPlayer->getState() == PlayerState::InjuringOverhead
                    || mPlayer->getState() == PlayerState::InjuringUpOverhead || mPlayer->getState() == PlayerState::InjuringDownOverhead)
                    continue;
            }
            //ngan di chuyen
            if (sidePlayer == Entity::SideCollisions::Right)
            {
                mPlayer->allowMoveRight = false;
            }
            else if (sidePlayer == Entity::SideCollisions::Left)
            {
                mPlayer->allowMoveLeft = false;
            }

            //kiem tra neu va cham voi gate
            if (listCollision.at(i)->Tag == Entity::EntityTypes::Gate)
            {
                if (sidePlayer == Entity::SideCollisions::Right)
                {
                    //chuyen sang map phai
                    mIsPassGateRight = true;
                }
                else if (sidePlayer == Entity::SideCollisions::Left)
                {
                    //chuyen sang map trai
                    mIsPassGateLeft = true;
                }
                else if (sidePlayer == Entity::SideCollisions::Top)
                {
                    mIsPassGateTop = true;
                }
                else if (sidePlayer == Entity::SideCollisions::Bottom)
                {
                    mIsPassGateBottom = true;
                }
            }

            if (listCollision[i]->Tag == Entity::EntityTypes::Overworld)
            {
                isReplace = true;
                SceneManager::GetInstance()->ReplaceScene(new FirstScene(oldPos, currReverse));
                return;
            }
        }
    }



    //xu ly enemy va cham
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        if (!mEnemies[i]->mIsActive)
            continue;
        for (size_t j = 0; j < listCollisionWithEnemy.size(); j++)
        {
            if (listCollisionWithEnemy[j]->Tag == Entity::EntityTypes::Dangers)
                continue;
            Entity::CollisionReturn r = Collision::RecteAndRect(mEnemies[i]->GetBound(),
                listCollisionWithEnemy.at(j)->GetBound());
            //string str = std::to_string(listCollision.at(i)->GetBound().top);
            //MessageBox(0, const_cast<char*>(str.c_str()), "test", 0);
            if (r.IsCollided)
            {
                //lay phia va cham cua Entity so voi Player
                Entity::SideCollisions sideEnemy = Collision::getSideCollision(mEnemies[i], r);

                //lay phia va cham cua Player so voi Entity
                Entity::SideCollisions sideImpactor = Collision::getSideCollision(listCollisionWithEnemy.at(j), r);

                //goi den ham xu ly collision cua Player va Entity
                mEnemies[i]->OnCollision(listCollisionWithEnemy.at(j), r, sideEnemy);
                listCollisionWithEnemy.at(j)->OnCollision(mEnemies[i], r, sideImpactor);
            }
        }

        //va cham bullet cannon
        for (size_t j = 0; j < listCollisionWithEnemy.size(); j++)
        {
            if (listCollisionWithEnemy[j]->Tag == Entity::EntityTypes::Dangers)
                continue;
            if (mEnemies[i]->mBullets.size() > 0 && (mEnemies[i]->type == Enemy::EnemyType::cannon || mEnemies[i]->type == Enemy::EnemyType::boss))
            {
                for (size_t k = 0; k < mEnemies[i]->mBullets.size(); k++)
                {
                    Entity::CollisionReturn r = Collision::RecteAndRect(mEnemies[i]->mBullets[k]->GetBound(),
                        listCollisionWithEnemy.at(j)->GetBound());
                    //string str = std::to_string(listCollision.at(i)->GetBound().top);
                    //MessageBox(0, const_cast<char*>(str.c_str()), "test", 0);
                    if (r.IsCollided)
                    {
                        mEnemies[i]->mBullets[k]->mIsValid = false;
                    }
                }
            }
        }
    }

    //xu ly enemy va cham voi dan
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        if (!mEnemies[i]->mIsActive)
            continue;
        for (size_t j = 0; j < mPlayer->mBullets.size(); j++)
        {
            Entity::CollisionReturn r = Collision::RecteAndRect(mEnemies[i]->GetBound(),
                mPlayer->mBullets.at(j)->GetBound());
            //string str = std::to_string(listCollision.at(i)->GetBound().top);
            //MessageBox(0, const_cast<char*>(str.c_str()), "test", 0);
            if (r.IsCollided)
            {
                //lay phia va cham cua Entity so voi Player
                Entity::SideCollisions sideEnemy = Collision::getSideCollision(mEnemies[i], r);

                //lay phia va cham cua Player so voi Entity
                Entity::SideCollisions sideImpactor = Collision::getSideCollision(mPlayer->mBullets.at(j), r);

                //goi den ham xu ly collision cua Player va Entity
                mEnemies[i]->OnCollision(mPlayer->mBullets.at(j), r, sideEnemy);
                mPlayer->mBullets.at(j)->OnCollision(mPlayer, r, sideImpactor);
            }
        }
    }

    //xu ly va cham hand boss
    if (mPlayer->getState() != PlayerState::InjuringOverhead && mPlayer->getState() != PlayerState::InjuringUpOverhead && mPlayer->getState() != PlayerState::InjuringDownOverhead)
    {
        if (mEnemies[mEnemies.size() - 1]->mIsActive)
        {
            for (int i = 0; i < 5; i++)
            {
                Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
                    mEnemies[mEnemies.size() - 1]->GetBossHandLeft()[i]->GetBound());
                if (r.IsCollided)
                {
                    //lay phia va cham cua Entity so voi Player
                    Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer, r);

                    //lay phia va cham cua Player so voi Entity
                    Entity::SideCollisions sideImpactor = Collision::getSideCollision(mEnemies[mEnemies.size() - 1]->GetBossHandLeft()[i], r);

                    //goi den ham xu ly collision cua Player va Entity
                    mPlayer->OnCollision(mEnemies[mEnemies.size() - 1]->GetBossHandLeft()[i], r, sidePlayer);
                }
            }
            for (int i = 0; i < 5; i++)
            {
                Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
                    mEnemies[mEnemies.size() - 1]->GetBossHandRight()[i]->GetBound());
                if (r.IsCollided)
                {
                    //lay phia va cham cua Entity so voi Player
                    Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer, r);

                    //lay phia va cham cua Player so voi Entity
                    Entity::SideCollisions sideImpactor = Collision::getSideCollision(mEnemies[mEnemies.size() - 1]->GetBossHandRight()[i], r);

                    //goi den ham xu ly collision cua Player va Entity
                    mPlayer->OnCollision(mEnemies[mEnemies.size() - 1]->GetBossHandRight()[i], r, sidePlayer);
                }
            }
        }
    }

    //xu ly player va cham voi enemy
    if (mPlayer->getState() != PlayerState::InjuringOverhead && mPlayer->getState() != PlayerState::InjuringUpOverhead && mPlayer->getState() != PlayerState::InjuringDownOverhead)
        for (size_t i = 0; i < mEnemies.size(); i++)
        {
            if (!mEnemies[i]->mIsActive)
                continue;
            Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
                mEnemies[i]->GetBound());
            //string str = std::to_string(listCollision.at(i)->GetBound().top);
            //MessageBox(0, const_cast<char*>(str.c_str()), "test", 0);
            if (r.IsCollided)
            {
                //lay phia va cham cua Entity so voi Player
                Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer, r);

                //lay phia va cham cua Player so voi Entity
                Entity::SideCollisions sideImpactor = Collision::getSideCollision(mEnemies[i], r);

                //goi den ham xu ly collision cua Player va Entity
                mPlayer->OnCollision(mEnemies[i], r, sidePlayer);
                mEnemies[i]->OnCollision(mPlayer, r, sideImpactor);

                //ngan di chuyen
                if (sidePlayer == Entity::SideCollisions::Right)
                {
                    mPlayer->allowMoveRight = false;
                    mPlayer->AddPosition(-10, 0);
                }
                else if (sidePlayer == Entity::SideCollisions::Left)
                {
                    mPlayer->allowMoveLeft = false;
                    mPlayer->AddPosition(10, 0);
                }
                else if (sidePlayer == Entity::SideCollisions::Bottom || sidePlayer == Entity::SideCollisions::BottomLeft || sidePlayer == Entity::SideCollisions::BottomRight)
                {
                    mPlayer->allowMoveDown = false;
                    mPlayer->AddPosition(0, -10);
                }
                else if (sidePlayer == Entity::SideCollisions::Top || sidePlayer == Entity::SideCollisions::TopLeft || sidePlayer == Entity::SideCollisions::TopRight)
                {
                    mPlayer->allowMoveUp = false;
                    mPlayer->AddPosition(0, 10);
                }
            }
        }

    //xu ly player va cham voi dan enemy
    if (mPlayer->getState() != PlayerState::InjuringOverhead && mPlayer->getState() != PlayerState::InjuringUpOverhead && mPlayer->getState() != PlayerState::InjuringDownOverhead)
        for (size_t i = 0; i < mEnemies.size(); i++)
        {
            if (!mEnemies[i]->mIsActive)
                continue;
            if (mEnemies[i]->mBullets.size() > 0)
            {
                for (size_t j = 0; j < mEnemies[i]->mBullets.size(); j++)
                {
                    Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
                        mEnemies[i]->mBullets[j]->GetBound());
                    //string str = std::to_string(listCollision.at(i)->GetBound().top);
                    //MessageBox(0, const_cast<char*>(str.c_str()), "test", 0);
                    if (r.IsCollided)
                    {
                        //lay phia va cham cua Entity so voi Player
                        Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer, r);

                        //lay phia va cham cua Player so voi Entity
                        Entity::SideCollisions sideImpactor = Collision::getSideCollision(mEnemies[i]->mBullets[j], r);

                        //goi den ham xu ly collision cua Player va Entity
                        mPlayer->OnCollision(mEnemies[i]->mBullets[j], r, sidePlayer);
                        mEnemies[i]->mBullets[j]->OnCollision(mPlayer, r, sideImpactor);
                    }
                }
            }
        }

    //xu ly player va cham voi power collection
    for (size_t i = 0; i < mItemCollections.size(); i++)
    {
        RECT bound;
        bound.top = mItemCollections[i]->mSprite->GetPosition().y;
        bound.left = mItemCollections[i]->mSprite->GetPosition().x;
        bound.bottom = bound.top + mItemCollections[i]->mSprite->GetHeight();
        bound.right = bound.left + mItemCollections[i]->mSprite->GetWidth();
        Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
            bound);
        if (r.IsCollided)
        {
            //add power
            if (mItemCollections[i]->kindItem == 1 && mPlayer->mPower < 8)
                mPlayer->mPower += 1;
            else if (mItemCollections[i]->kindItem == 6)
            {
                GameSound::GetInstance()->Play("Assets/Sounds/area_clear.mp3");
                if (mPlayer->getState() == PlayerState::RunningUpOverhead)
                    mPlayer->SetState(new PlayerStandingUpOverheadState(mPlayer->getPlayerData()));
                else if (mPlayer->getState() == PlayerState::RunningDownOverhead)
                    mPlayer->SetState(new PlayerStandingDownOverheadState(mPlayer->getPlayerData()));
                else if (mPlayer->getState() == PlayerState::RunningOverhead)
                    mPlayer->SetState(new PlayerStandingOverheadState(mPlayer->getPlayerData()));
                mPlayer->SetVx(0);
                mPlayer->SetVy(0);
                mIsKilledBoss = true;
            }
            mItemCollections.erase(mItemCollections.begin() + i);
        }
    }

    //xu ly va cham da
    for (size_t i = 0; i < mRocks.size(); i++)
    {
        Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
            mRocks[i]->GetBound());
        if (r.IsCollided)
        {
            Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer, r);

            //lay phia va cham cua Player so voi Entity
            Entity::SideCollisions sideImpactor = Collision::getSideCollision(mRocks.at(i), r);

            //goi den ham xu ly collision cua Player va Entity
            mPlayer->OnCollision(listCollision.at(i), r, sidePlayer);
            mRocks.at(i)->OnCollision(mPlayer, r, sideImpactor);

            //ngan di chuyen
            if (sidePlayer == Entity::SideCollisions::Right)
            {
                mPlayer->allowMoveRight = false;
            }
            else if (sidePlayer == Entity::SideCollisions::Left)
            {
                mPlayer->allowMoveLeft = false;
            }
            else if (sidePlayer == Entity::SideCollisions::Top || sidePlayer == Entity::SideCollisions::TopLeft || sidePlayer == Entity::SideCollisions::TopRight)
            {
                mPlayer->allowMoveUp = false;
            }
            else if (sidePlayer == Entity::SideCollisions::Bottom || sidePlayer == Entity::SideCollisions::BottomLeft || sidePlayer == Entity::SideCollisions::BottomRight)
            {
                mPlayer->allowMoveDown = false;
            }
        }
        
    }

    //xu ly dan va cham
    for (int i = 0; i < mPlayer->mBullets.size(); i++)
    {
        for (size_t j = 0; j < listCollisionWithBullet.size(); j++)
        {
            Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->mBullets[i]->GetBound(), listCollisionWithBullet.at(j)->GetBound());
            if (r.IsCollided)
            {
                //lay phia va cham cua Entity so voi Bullet
                Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer->mBullets[i], r);

                //lay phia va cham cua Bullet so voi Entity
                Entity::SideCollisions sideImpactor = Collision::getSideCollision(listCollisionWithBullet.at(j), r);

                //goi den ham xu ly collision cua Bullet va Entity
                mPlayer->mBullets[i]->OnCollision(listCollisionWithBullet.at(j), r, sidePlayer);
                listCollisionWithBullet.at(j)->OnCollision(mPlayer->mBullets[i], r, sideImpactor);
                break;
            }
        }
        for (size_t j = 0; j < mRocks.size(); j++)
        {
            Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->mBullets[i]->GetBound(), mRocks.at(j)->GetBound());
            if (r.IsCollided)
            {
                //lay phia va cham cua Entity so voi Bullet
                Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer->mBullets[i], r);

                //lay phia va cham cua Bullet so voi Entity
                Entity::SideCollisions sideImpactor = Collision::getSideCollision(listCollisionWithBullet.at(j), r);

                //goi den ham xu ly collision cua Bullet va Entity
                mPlayer->mBullets[i]->OnCollision(mRocks.at(j), r, sidePlayer);
                mRocks.at(j)->OnCollision(mPlayer->mBullets[i], r, sideImpactor);
                if (mRocks.at(j)->mDestroyed)
                {
                    if (mRocks[j]->mItem)
                        mItemCollections.push_back(mRocks[j]->mItem);
                    delete mRocks[j];
                    mRocks.erase(mRocks.begin() + j);
                }
                break;
            }
        }
    }
}

void ThirdScene::PassGateRight()
{
    if (mCamera->GetPosition().x < mCurrentMapBound.right + GameGlobal::GetWidth() / 2)
    {
        mCamera->SetPosition(mCamera->GetPosition().x + 10, mCamera->GetPosition().y);
        if (mPlayer->GetPosition().x <= mCurrentMapBound.right + 120)
        {
            mPlayer->SetVx(240);
            mPlayer->SetVy(0);
            mPlayer->SetState(new PlayerRunningOverheadState(mPlayer->getPlayerData()));
        }
    }
    else
    {
        if (mPlayer->GetPosition().x <= mCamera->GetBound().left + 120)
        {
            mPlayer->SetVx(240);
            mPlayer->SetVy(0);
            mPlayer->SetState(new PlayerRunningOverheadState(mPlayer->getPlayerData()));
        }
        else
        {
            mPlayer->SetVx(0);
            mPlayer->SetState(new PlayerStandingOverheadState(mPlayer->getPlayerData()));

            //set bound submap
            for (int i = 0; i < 21; i++)
            {
                if (mListMapBound[i].left < mPlayer->GetPosition().x && mListMapBound[i].right > mPlayer->GetPosition().x
                    && mListMapBound[i].top < mPlayer->GetPosition().y && mListMapBound[i].bottom > mPlayer->GetPosition().y)
                {
                    mCurrentMapBound = mListMapBound[i];
                    break;
                }
            }
            mIsPassGateRight = false;
        }
    }
}

void ThirdScene::PassGateLeft()
{
    if (mCamera->GetPosition().x > mCurrentMapBound.left - GameGlobal::GetWidth() / 2)
    {
        mCamera->SetPosition(mCamera->GetPosition().x - 10, mCamera->GetPosition().y);
        if (mPlayer->GetPosition().x >= mCurrentMapBound.left - 120)
        {
            mPlayer->SetVx(-240);
            mPlayer->SetVy(0);
            mPlayer->SetState(new PlayerRunningOverheadState(mPlayer->getPlayerData()));
        }
    }
    else
    {
        if (mPlayer->GetPosition().x >= mCamera->GetBound().right - 120)
        {
            mPlayer->SetVy(0);
            mPlayer->SetVx(-240);
            mPlayer->SetState(new PlayerRunningOverheadState(mPlayer->getPlayerData()));
        }
        else
        {
            mPlayer->SetVx(0);
            mPlayer->SetState(new PlayerStandingOverheadState(mPlayer->getPlayerData()));

            //set bound submap
            for (int i = 0; i < 21; i++)
            {
                if (mListMapBound[i].left < mPlayer->GetPosition().x && mListMapBound[i].right > mPlayer->GetPosition().x
                    && mListMapBound[i].top < mPlayer->GetPosition().y && mListMapBound[i].bottom > mPlayer->GetPosition().y)
                {
                    mCurrentMapBound = mListMapBound[i];
                    break;
                }
            }
            mIsPassGateLeft = false;
        }
    }
}

void ThirdScene::PassGateTop()
{
    if (mCamera->GetPosition().y > mCurrentMapBound.top - GameGlobal::GetWidth() / 2)
    {
        mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetPosition().y - 10);
        if (mPlayer->GetPosition().y >= mCurrentMapBound.top - 120)
        {
            mPlayer->SetVy(-240);
            mPlayer->SetVx(0);
            mPlayer->SetState(new PlayerRunningUpOverheadState(mPlayer->getPlayerData()));
        }
    }
    else
    {
        if (mPlayer->GetPosition().y >= mCamera->GetBound().bottom - 120)
        {
            mPlayer->SetVx(0);
            mPlayer->SetVy(-240);
            mPlayer->SetState(new PlayerRunningUpOverheadState(mPlayer->getPlayerData()));
        }
        else
        {
            mPlayer->SetVy(0);
            mPlayer->SetState(new PlayerStandingUpOverheadState(mPlayer->getPlayerData()));

            //set bound submap
            for (int i = 0; i < 21; i++)
            {
                if (mListMapBound[i].left < mPlayer->GetPosition().x && mListMapBound[i].right > mPlayer->GetPosition().x
                    && mListMapBound[i].top < mPlayer->GetPosition().y && mListMapBound[i].bottom > mPlayer->GetPosition().y)
                {
                    mCurrentMapBound = mListMapBound[i];
                    if (i == 20)
                    {
                        GameSound::GetInstance()->Stop("area2");
                        GameSound::GetInstance()->Play("Assets/Sounds/preBoss.mp3");
                        mIsBossStage = true;
                        bossStage->SetPosition(1792, 1216);
                        bossBackground->SetPosition(1792, 1216);
                    }
                    break;
                }
            }
            mIsPassGateTop = false;
        }
    }
}

void ThirdScene::PassGateBottom()
{
    if (mCamera->GetPosition().y < mCurrentMapBound.bottom + GameGlobal::GetWidth() / 2)
    {
        mCamera->SetPosition(mCamera->GetPosition().x, mCamera->GetPosition().y + 10);
        if (mPlayer->GetPosition().y <= mCurrentMapBound.bottom + 120)
        {
            mPlayer->SetVy(240);
            mPlayer->SetVx(0);
            mPlayer->SetState(new PlayerRunningDownOverheadState(mPlayer->getPlayerData()));
        }
    }
    else
    {
        if (mPlayer->GetPosition().y <= mCamera->GetBound().top + 120)
        {
            mPlayer->SetVx(0);
            mPlayer->SetVy(240);
            mPlayer->SetState(new PlayerRunningDownOverheadState(mPlayer->getPlayerData()));
        }
        else
        {
            mPlayer->SetVy(0);
            mPlayer->SetState(new PlayerStandingDownOverheadState(mPlayer->getPlayerData()));

            //set bound submap
            for (int i = 0; i < 21; i++)
            {
                if (mListMapBound[i].left < mPlayer->GetPosition().x && mListMapBound[i].right > mPlayer->GetPosition().x
                    && mListMapBound[i].top < mPlayer->GetPosition().y && mListMapBound[i].bottom > mPlayer->GetPosition().y)
                {
                    mCurrentMapBound = mListMapBound[i];
                    break;
                }
            }
            mIsPassGateBottom = false;
        }
    }
}

void ThirdScene::Draw()
{
    //goi va draw cac sprite trong vector
    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
        GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
    mMap->Draw();
    if (mIsBossStage) bossStage->Draw(trans);
    if (mIsLoadedBossStage) bossBackground->Draw(bossBackground->GetPosition(), RECT(), D3DXVECTOR2(), trans);
    mPlayer->Draw();
    if (!mIsBossStage && !mIsLoadedBossStage) mMap->DrawWalls();
    if (mIsPassGateLeft || mIsPassGateRight || mIsPassGateBottom || mIsPassGateTop)
        mMap->DrawGates();
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        if (mEnemies[i]->mIsActive)
            mEnemies.at(i)->Draw(trans);
    }
    for (size_t i = 0; i < mItemCollections.size(); i++)
    {
        mItemCollections.at(i)->mSprite->Draw(mItemCollections[i]->mSprite->GetPosition(), RECT(), D3DXVECTOR2(), trans);
    }
    for (size_t i = 0; i < mRocks.size(); i++)
    {
        mRocks.at(i)->Draw(mRocks[i]->GetPosition(), RECT(), D3DXVECTOR2(), trans);
    }
    mPlayer->DrawPower();
}

void ThirdScene::OnKeyDown(int keyCode)
{
    keys[keyCode] = true;
    mPlayer->OnKeyPressed(keyCode);
}

void ThirdScene::OnKeyUp(int keyCode)
{
    keys[keyCode] = false;
    mPlayer->OnKeyUp(keyCode);
}

void ThirdScene::OnMouseDown(float x, float y)
{

}