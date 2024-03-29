#include "FirstScene.h"
#include "../Player.h"
#include "../GameDefines.h"
#include <string>
#include <fstream>

FirstScene::FirstScene()
{
    LoadContent();
}

void FirstScene::LoadContent()
{
    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x1E1E1E;

    mMap = new Map("Assets/area2.tmx");
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - GameGlobal::GetHeight() / 2);
    mMap->SetCamera(mCamera);

    LoadEnemies("Assets/enemies.txt");

    //get bound submap
    mListMapBound = new RECT[15];
    LoadMapBound("Assets/map_bounds.txt");
    mCurrentMapBound = mListMapBound[0];

    mPlayer = new Player();
    mPlayer->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - GameGlobal::GetHeight() / 2);
    mPlayer->SetCamera(mCamera);
}

const vector<string> explode(const string& s, const char& c)
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

void FirstScene::LoadMapBound(const char* path)
{
    //left->top->bottom->right
    fstream f;
    f.open(path, std::ios::in);
    int i = 0;
    while (!f.eof())
    {
        string line;
        std::getline(f, line);
        vector<string> info = { explode(line, ' ') };
        mListMapBound[i].left = stoi(info[0]);
        mListMapBound[i].top = stoi(info[1]);
        mListMapBound[i].bottom = stoi(info[2]);
        mListMapBound[i].right = stoi(info[3]);
        i++;
    }
    f.close();
}

void FirstScene::LoadEnemies(const char* path)
{
    // worm = 1, dome = 2, floater = 3, jumper = 4
    fstream f;
    f.open(path, std::ios::in);
    while (!f.eof())
    {
        string line;
        std::getline(f, line);
        vector<string> info = { explode(line, ' ') };
        if (info[0] == "1")
        {
            mEnemies.push_back(new Worm(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3]), stoi(info[4])));
        }
        else if (info[0] == "2")
        {
            mEnemies.push_back(new Dome(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3]), stoi(info[4])));
        }
        else if (info[0] == "3")
        {
            mEnemies.push_back(new Floater(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3]), stoi(info[4])));
        }
        else if (info[0] == "4")
        {
            mEnemies.push_back(new Jumper(D3DXVECTOR3(stoi(info[1]), stoi(info[2]), 0), stoi(info[3]), stoi(info[4])));
        }
    }
    f.close();
}

void FirstScene::Update(float dt)
{
    if (!mIsPassGateRight && !mIsPassGateLeft) checkCollision();
    mMap->Update(dt);
    if (!mIsPassGateRight && !mIsPassGateLeft) mPlayer->HandleKeyboard(keys);
    mPlayer->Update(dt);
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        if (mEnemies[i] && mEnemies[i]->GetHP() > 0)
        {
            if (mEnemies[i]->GetPosition().x > mCamera->GetBound().left - mEnemies[i]->GetWidth() / 2 && mEnemies[i]->GetPosition().x < mCamera->GetBound().right + mEnemies[i]->GetWidth() / 2
                && mEnemies[i]->GetPosition().y > mCamera->GetBound().top - mEnemies[i]->GetHeight() / 2 && mEnemies[i]->GetPosition().y < mCamera->GetBound().bottom + mEnemies[i]->GetHeight() / 2)
            {
                mEnemies[i]->mIsActive = true;
                if (mEnemies[i]->type == Enemy::EnemyType::floater && mEnemies[i]->mBullets.size() == 0)
                {
                    mEnemies[i]->mBullets.push_back(new BulletFloater(D3DXVECTOR3(mEnemies[i]->GetPosition().x, mEnemies[i]->GetPosition().y + 10, 0)));
                    mEnemies[i]->mBullets[0]->AddVx((mPlayer->GetPosition().x - mEnemies[i]->mBullets[0]->GetPosition().x));
                    mEnemies[i]->mBullets[0]->AddVy((mPlayer->GetPosition().y - mEnemies[i]->mBullets[0]->GetPosition().y));
                }
            }
            else mEnemies[i]->mIsActive = false;
            /*if (mEnemies[i]->mIsActive && mEnemies[i]->GetPosition().x < mPlayer->GetPosition().x)
            {
                if (mEnemies[i]->GetVy() == 0)
                    mEnemies[i]->SetVx(50);
            }
            else if (mEnemies[i]->mIsActive)
            {
                if (mEnemies[i]->GetVy() == 0)
                    mEnemies[i]->SetVx(-50);
            }*/
            if (mEnemies[i]->mIsActive && mEnemies[i]->GetVy() == 0 && mEnemies[i]->GetVx() == 0)
            {
                mEnemies[i]->SetVx(-40);
                if (mEnemies[i]->type == Enemy::EnemyType::jumper) mEnemies[i]->SetVy(-40);
                if (mEnemies[i]->type == Enemy::EnemyType::floater) mEnemies[i]->SetVy(40);
            }
            if (mEnemies[i]->mIsActive)
                mEnemies.at(i)->Update(dt);
        }
        else
        {
            if (mEnemies[i]->mIsContainItem == 1)
            {
                mPowerCollections.push_back(new Sprite("Assets/powerCollection.png"));
                mPowerCollections.at(mPowerCollections.size() - 1)->SetPosition(D3DXVECTOR3(mEnemies.at(i)->GetPosition().x, mEnemies.at(i)->GetPosition().y - 8, 0));
            }
            mEnemies.erase(mEnemies.begin() + i);
        }
    }
    if (!mIsPassGateRight && !mIsPassGateLeft) CheckCameraAndWorldMap();
    if (mIsPassGateRight) PassGateRight();
    if (mIsPassGateLeft) PassGateLeft();
}

void FirstScene::CheckCameraAndWorldMap()
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

void FirstScene::checkCollision()
{
    /*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
    dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
    int widthBottom = 0;

    vector<Entity*> listCollision;
    vector<Entity*> listCollisionWithBullet;
    vector<Entity*> listCollisionWithEnemy;

    mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);
    for (int i = 0; i < mPlayer->mBullets.size(); i++)
        mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithBullet, mPlayer->mBullets[i]);
    for (size_t i = 0; i < mEnemies.size(); i++)
        mMap->GetQuadTree()->getEntitiesCollideAble(listCollisionWithEnemy, mEnemies[i]);
    for (size_t i = 0; i < listCollision.size(); i++)
    {
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
            }

            //kiem tra neu va cham voi phia duoi cua Player 
            if (sidePlayer == Entity::Bottom || sidePlayer == Entity::BottomLeft
                || sidePlayer == Entity::BottomRight)
            {
                //kiem cha do dai ma mario tiep xuc phia duoi day
                int bot = r.RegionCollision.right - r.RegionCollision.left;

                if (bot > widthBottom)
                    widthBottom = bot;
            }
        }
    }

    //xu ly enemy va cham
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        if (mEnemies[i]->type == Enemy::EnemyType::floater)
            mEnemies[i]->widthBottom = 9;
        else
            mEnemies[i]->widthBottom = 0;
        for (size_t j = 0; j < listCollisionWithEnemy.size(); j++)
        {
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

                //ngan di chuyen
                if (sideEnemy == Entity::SideCollisions::Right)
                {
                    //mPlayer->allowMoveRight = false;
                }
                else if (sideEnemy == Entity::SideCollisions::Left)
                {
                    //mPlayer->allowMoveLeft = false;
                }

                //kiem tra neu va cham voi gate
                if (listCollisionWithEnemy.at(j)->Tag == Entity::EntityTypes::Gate)
                {
                    
                }

                //kiem tra neu va cham voi phia duoi cua Player 
                if (sideEnemy == Entity::Bottom || sideEnemy == Entity::BottomLeft
                    || sideEnemy == Entity::BottomRight)
                {
                    //kiem cha do dai ma mario tiep xuc phia duoi day
                    int bot = r.RegionCollision.right - r.RegionCollision.left;

                    if (bot > mEnemies[i]->widthBottom)
                        mEnemies[i]->widthBottom = bot;
                }
            }
        }
    }

    //xu ly enemy va cham voi dan
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
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

                //ngan di chuyen
                if (sideEnemy == Entity::SideCollisions::Right)
                {
                    //mPlayer->allowMoveRight = false;
                }
                else if (sideEnemy == Entity::SideCollisions::Left)
                {
                    //mPlayer->allowMoveLeft = false;
                }

                //kiem tra neu va cham voi phia duoi cua Player 
                if (sideEnemy == Entity::Bottom || sideEnemy == Entity::BottomLeft
                    || sideEnemy == Entity::BottomRight)
                {
                    //kiem cha do dai ma mario tiep xuc phia duoi day
                    int bot = r.RegionCollision.right - r.RegionCollision.left;

                    if (bot > mEnemies[i]->widthBottom)
                        mEnemies[i]->widthBottom = bot;
                }
            }
        }
    }

    //xu ly player va cham voi enemy
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
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
            else if (sidePlayer == Entity::SideCollisions::Bottom)
            {
                mPlayer->AddPosition(10, -10);
            }
            //tru power
            if (mPlayer->mPower > 0)
                mPlayer->mPower -= 1;
        }
    }

    //xu ly player va cham voi dan enemy
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        if (mEnemies[i]->mBullets.size() > 0)
        {
            Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
                mEnemies[i]->mBullets[0]->GetBound());
            //string str = std::to_string(listCollision.at(i)->GetBound().top);
            //MessageBox(0, const_cast<char*>(str.c_str()), "test", 0);
            if (r.IsCollided)
            {
                //lay phia va cham cua Entity so voi Player
                Entity::SideCollisions sidePlayer = Collision::getSideCollision(mPlayer, r);

                //lay phia va cham cua Player so voi Entity
                Entity::SideCollisions sideImpactor = Collision::getSideCollision(mEnemies[i]->mBullets[0], r);

                //goi den ham xu ly collision cua Player va Entity
                mPlayer->OnCollision(mEnemies[i]->mBullets[0], r, sidePlayer);
                mEnemies[i]->mBullets[0]->OnCollision(mPlayer, r, sideImpactor);

                //tru power
                if (mPlayer->mPower > 0)
                    mPlayer->mPower -= 1;
            }
        }
    }

    //xu ly player va cham voi power collection
    for (size_t i = 0; i < mPowerCollections.size(); i++)
    {
        RECT bound;
        bound.top = mPowerCollections[i]->GetPosition().y;
        bound.left = mPowerCollections[i]->GetPosition().x;
        bound.bottom = bound.top + mPowerCollections[i]->GetHeight();
        bound.right = bound.left + mPowerCollections[i]->GetWidth();
        Entity::CollisionReturn r = Collision::RecteAndRect(mPlayer->GetBound(),
            bound);
        //string str = std::to_string(listCollision.at(i)->GetBound().top);
        //MessageBox(0, const_cast<char*>(str.c_str()), "test", 0);
        if (r.IsCollided)
        {
            mPowerCollections.erase(mPowerCollections.begin() + i);
            //tru power
            if (mPlayer->mPower < 8)
                mPlayer->mPower += 1;
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
    }

    //Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat    
    if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
    {
        mPlayer->OnNoCollisionWithBottom();
    }
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        if (mEnemies[i]->widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
        {
            mEnemies[i]->OnNoCollisionWithBottom();
        }
    }
}

void FirstScene::PassGateRight()
{
    if (mCamera->GetPosition().x < mCurrentMapBound.right + GameGlobal::GetWidth() / 2)
    {
        mCamera->SetPosition(mCamera->GetPosition().x + 10, mCamera->GetPosition().y);
        if (mPlayer->GetPosition().x <= mCurrentMapBound.right + 192)
        {
            mPlayer->SetVx(240);
            mPlayer->SetVy(0);
            mPlayer->SetState(new PlayerRunningState(mPlayer->getPlayerData()));
        }
    }
    else
    {
        if (mPlayer->GetPosition().x <= mCamera->GetBound().left + 192)
        {
            mPlayer->SetVx(240);
            mPlayer->SetVy(0);
            mPlayer->SetState(new PlayerRunningState(mPlayer->getPlayerData()));
        }
        else
        {
            mPlayer->SetVx(0);
            mPlayer->SetState(new PlayerStandingState(mPlayer->getPlayerData()));

            //set bound submap
            for (int i = 0; i < 15; i++)
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

void FirstScene::PassGateLeft()
{
    if (mCamera->GetPosition().x > mCurrentMapBound.left - GameGlobal::GetWidth() / 2)
    {
        mCamera->SetPosition(mCamera->GetPosition().x - 10, mCamera->GetPosition().y);
        if (mPlayer->GetPosition().x >= mCurrentMapBound.left - 192)
        {
            mPlayer->SetVx(-240);
            mPlayer->SetVy(0);
            mPlayer->SetState(new PlayerRunningState(mPlayer->getPlayerData()));
        }
    }
    else
    {
        if (mPlayer->GetPosition().x >= mCamera->GetBound().right - 192)
        {
            mPlayer->SetVy(0);
            mPlayer->SetVx(-240);
            mPlayer->SetState(new PlayerRunningState(mPlayer->getPlayerData()));
        }
        else
        {
            mPlayer->SetVx(0);
            mPlayer->SetState(new PlayerStandingState(mPlayer->getPlayerData()));

            //set bound submap
            for (int i = 0; i < 15; i++)
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

void FirstScene::Draw()
{
    //goi va draw cac sprite trong vector

    mMap->Draw();
    mPlayer->Draw();
    if (mIsPassGateLeft || mIsPassGateRight)
        mMap->DrawGates();
    for (size_t i = 0; i < mEnemies.size(); i++)
    {
        D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
            GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
        if (mEnemies[i]->mIsActive)
            mEnemies.at(i)->Draw(trans);
    }
    for (size_t i = 0; i < mPowerCollections.size(); i++)
    {
        D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
            GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);
        mPowerCollections.at(i)->Draw(mPowerCollections[i]->GetPosition(), RECT(), D3DXVECTOR2(), trans);
    }
}

void FirstScene::OnKeyDown(int keyCode)
{
    keys[keyCode] = true;
    mPlayer->OnKeyPressed(keyCode);
}

void FirstScene::OnKeyUp(int keyCode)
{
    keys[keyCode] = false;
    mPlayer->OnKeyUp(keyCode);
}

void FirstScene::OnMouseDown(float x, float y)
{

}