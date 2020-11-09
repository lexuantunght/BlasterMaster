#include "Map2Scene.h"
#include "../Player.h"
#include "../GameDefines.h"
#include "../SceneManager.h"
#include "Map1Scene.h"
#include <string>

Map2Scene::Map2Scene()
{
    LoadContent();
}

Map2Scene::~Map2Scene()
{

}

void Map2Scene::LoadContent()
{

    //set mau backcolor cho scene o day la mau xanh
    mBackColor = 0x1E1E1E;

    mMap = new Map("Assets/area2_map2.tmx");
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    mCamera->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - GameGlobal::GetHeight() / 2);
    mMap->SetCamera(mCamera);

    mPlayer = new Player();
    mPlayer->SetPosition(GameGlobal::GetWidth() / 2, mMap->GetHeight() - GameGlobal::GetHeight() / 2);
    mPlayer->SetCamera(mCamera);
}

void Map2Scene::Update(float dt)
{
    checkCollision();
    mMap->Update(dt);
    mPlayer->HandleKeyboard(keys);
    mPlayer->Update(dt);
    CheckCameraAndWorldMap();
}

void Map2Scene::checkCollision()
{
    /*su dung de kiem tra xem khi nao mario khong dung tren 1 object hoac
    dung qua sat mep trai hoac phai cua object do thi se chuyen state la falling*/
    int widthBottom = 0;

    vector<Entity*> listCollision;

    mMap->GetQuadTree()->getEntitiesCollideAble(listCollision, mPlayer);
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
                }
                else if (sidePlayer == Entity::SideCollisions::Left)
                {
                    //chuyen sang map trai
                    SceneManager::GetInstance()->ReplaceScene(new Map1Scene());
                    return;
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

    //Neu mario dung ngoai mep thi luc nay cho mario rot xuong duoi dat    
    if (widthBottom < Define::PLAYER_BOTTOM_RANGE_FALLING)
    {
        mPlayer->OnNoCollisionWithBottom();
    }
}