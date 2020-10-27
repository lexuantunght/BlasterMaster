#include "Map.h"

Map::Map(const char* filePath)
{
    mCamera = new Camera(GameGlobal::GetWidth(), GameGlobal::GetHeight());
    LoadMap(filePath);
}

Map::~Map()
{
    delete mMap;

    for (size_t i = 0; i < mBees.size(); i++)
    {
        if (mBees[i])
            delete mBees[i];
    }
    mBees.clear();

    for (size_t i = 0; i < mListTileset.size(); i++)
    {
        if (mListTileset[i])
            delete mListTileset[i];
    }
    mListTileset.clear();
}

void Map::LoadMap(const char* filePath)
{
    mMap = new Tmx::Map();
    mMap->ParseFile(filePath);

    RECT r;
    r.left = 0;
    r.top = 0;
    r.right = this->GetWidth();
    r.bottom = this->GetHeight();

    mQuadTree = new QuadTree(1, r);
    
    //load cac tiled
    for (size_t i = 0; i < mMap->GetNumTilesets(); i++)
    {
        const Tmx::Tileset* tileset = mMap->GetTileset(i);

        Sprite* sprite = new Sprite(tileset->GetImage()->GetSource().c_str());

        mListTileset.insert(std::pair<int, Sprite*>(i, sprite));
    }

    // load cac object
    for (size_t i = 0; i < GetMap()->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer* layer = mMap->GetTileLayer(i);

        if (layer->IsVisible())
            continue;

        //xac dinh layer Brick bi an di de tu do tao ra cac vien gach trong game, nhung vien gach khong phai la 1 physic static nos co the bi pha huy duoc

        if (layer->GetName() == "BEE")
        {
            for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
            {
                const Tmx::Tileset* tileSet = mMap->GetTileset(j);

                int tileWidth = mMap->GetTileWidth();
                int tileHeight = mMap->GetTileHeight();

                int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
                int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;
               
                for (size_t m = 0; m < layer->GetHeight(); m+=2)
                {
                    for (size_t n = 0; n < layer->GetWidth(); n+=2)
                    {
                        if (layer->GetTileTilesetIndex(n, m) != -1)
                        {
                            int tileID = layer->GetTileId(n, m);

                            int y = tileID / tileSetWidth;
                            int x = tileID - y * tileSetWidth;

                            RECT sourceRECT;
                            sourceRECT.top = y * tileHeight;
                            sourceRECT.bottom = sourceRECT.top + tileHeight;
                            sourceRECT.left = x * tileWidth;
                            sourceRECT.right = sourceRECT.left + tileWidth;

                            RECT bound;
                            bound.left = n * tileWidth;
                            bound.top = m * tileHeight;
                            bound.right = bound.left + tileWidth;
                            bound.bottom = bound.top + tileHeight;

                            D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

                            Bee* bee = nullptr;

                            bee = new Bee(position);
                            bee->Tag = Entity::EntityTypes::Bee;
                            mBees.push_back(bee);
                            MessageBox(0, "", "", 0);
                            if (bee)
                                mQuadTree->insertEntity(bee);
                        }
                    }
                }
            }
        }
    }

    // load cac static tile
    for (size_t i = 0; i < mMap->GetNumObjectGroups(); i++)
    {
        const Tmx::ObjectGroup* objectGroup = mMap->GetObjectGroup(i);

        for (size_t j = 0; j < objectGroup->GetNumObjects(); j++)
        {
            //lay object group chu khong phai layer
            //object group se chua nhung body
            Tmx::Object* object = objectGroup->GetObjects().at(j);

            Entity* entity = new Entity();
            entity->SetPosition(object->GetX() + object->GetWidth() / 2,
                object->GetY() + object->GetHeight() / 2);
            entity->SetWidth(object->GetWidth());
            entity->SetHeight(object->GetHeight());
            if (objectGroup->GetName() == "GATES")
                entity->Tag = Entity::EntityTypes::Gate;
            else entity->Tag = Entity::EntityTypes::Static;

            mQuadTree->insertEntity(entity);
        }
    }
}

bool Map::isContain(RECT rect1, RECT rect2)
{
    if (rect1.left > rect2.right || rect1.right < rect2.left || rect1.top > rect2.bottom || rect1.bottom < rect2.top)
    {
        return false;
    }

    return true;
}

Tmx::Map* Map::GetMap()
{
    return mMap;
}

RECT Map::GetWorldMapBound()
{
    RECT bound;
    bound.left = bound.top = 0;
    bound.right = mMap->GetWidth() * mMap->GetTileWidth();
    bound.bottom = mMap->GetHeight() * mMap->GetTileHeight();

    return bound;
}

int Map::GetWidth()
{
    return mMap->GetWidth() * mMap->GetTileWidth();
}

int Map::GetHeight()
{
    return mMap->GetHeight() * mMap->GetTileHeight();
}

int Map::GetTileWidth()
{
    return mMap->GetTileWidth();
}

int Map::GetTileHeight()
{
    return mMap->GetTileHeight();
}

bool Map::IsBoundLeft()
{
    return (mCamera->GetBound().left == 0);
}

bool Map::IsBoundRight()
{
    return (mCamera->GetBound().right == this->GetWidth());
}

bool Map::IsBoundTop()
{
    return (mCamera->GetBound().top == 0);
}

bool Map::IsBoundBottom()
{
    return (mCamera->GetBound().bottom == this->GetHeight());
}

void Map::Update(float dt)
{
    for (size_t i = 0; i < mBees.size(); i++)
    {
        mBees[i]->Update(dt);
    }
}

void Map::Draw()
{
    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
        GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

    for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer* layer = mMap->GetTileLayer(i);

        if (!layer->IsVisible())
        {
            continue;
        }

        for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
        {
            const Tmx::Tileset* tileSet = mMap->GetTileset(j);

            RECT sourceRECT;

            int tileWidth = mMap->GetTileWidth();
            int tileHeight = mMap->GetTileHeight();

            int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
            int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

            for (size_t m = 0; m < layer->GetHeight(); m++)
            {
                for (size_t n = 0; n < layer->GetWidth(); n++)
                {
                    if (layer->GetTileTilesetIndex(n, m) != -1)
                    {
                        int tileID = layer->GetTileId(n, m);

                        int y = tileID / tileSetWidth;
                        int x = tileID - y * tileSetWidth;

                        sourceRECT.top = y * tileHeight;
                        sourceRECT.bottom = sourceRECT.top + tileHeight;
                        sourceRECT.left = x * tileWidth;
                        sourceRECT.right = sourceRECT.left + tileWidth;

                        Sprite* sprite = mListTileset[j];

                        //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                        //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
                        D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

                        if (mCamera != NULL)
                        {
                            RECT objRECT;
                            objRECT.left = position.x - tileWidth / 2;
                            objRECT.top = position.y - tileHeight / 2;
                            objRECT.right = objRECT.left + tileWidth;
                            objRECT.bottom = objRECT.top + tileHeight;

                            if (!Collision::RecteAndRect(mCamera->GetBound(), objRECT).IsCollided)
                                continue;
                        }

                        sprite->SetWidth(tileWidth);
                        sprite->SetHeight(tileHeight);

                        sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
                    }
                }
            }
        }
    }

    for (size_t i = 0; i < mBees.size(); i++)
    {
        mBees[i]->Draw(trans);
    }
}

void Map::DrawGates()
{
    D3DXVECTOR2 trans = D3DXVECTOR2(GameGlobal::GetWidth() / 2 - mCamera->GetPosition().x,
        GameGlobal::GetHeight() / 2 - mCamera->GetPosition().y);

    for (size_t i = 0; i < mMap->GetNumTileLayers(); i++)
    {
        const Tmx::TileLayer* layer = mMap->GetTileLayer(i);

        if (layer->GetName() == "GATES")
        {
            for (size_t j = 0; j < mMap->GetNumTilesets(); j++)
            {
                const Tmx::Tileset* tileSet = mMap->GetTileset(j);

                RECT sourceRECT;

                int tileWidth = mMap->GetTileWidth();
                int tileHeight = mMap->GetTileHeight();

                int tileSetWidth = tileSet->GetImage()->GetWidth() / tileWidth;
                int tileSetHeight = tileSet->GetImage()->GetHeight() / tileHeight;

                for (size_t m = 0; m < layer->GetHeight(); m++)
                {
                    for (size_t n = 0; n < layer->GetWidth(); n++)
                    {
                        if (layer->GetTileTilesetIndex(n, m) != -1)
                        {
                            int tileID = layer->GetTileId(n, m);

                            int y = tileID / tileSetWidth;
                            int x = tileID - y * tileSetWidth;

                            sourceRECT.top = y * tileHeight;
                            sourceRECT.bottom = sourceRECT.top + tileHeight;
                            sourceRECT.left = x * tileWidth;
                            sourceRECT.right = sourceRECT.left + tileWidth;

                            Sprite* sprite = mListTileset[j];

                            //tru tilewidth/2 va tileheight/2 vi Sprite ve o vi tri giua hinh anh cho nen doi hinh de cho
                            //dung toa do (0,0) cua the gioi thuc la (0,0) neu khong thi se la (-tilewidth/2, -tileheigth/2);
                            D3DXVECTOR3 position(n * tileWidth + tileWidth / 2, m * tileHeight + tileHeight / 2, 0);

                            if (mCamera != NULL)
                            {
                                RECT objRECT;
                                objRECT.left = position.x - tileWidth / 2;
                                objRECT.top = position.y - tileHeight / 2;
                                objRECT.right = objRECT.left + tileWidth;
                                objRECT.bottom = objRECT.top + tileHeight;

                                if (!Collision::RecteAndRect(mCamera->GetBound(), objRECT).IsCollided)
                                    continue;
                            }

                            sprite->SetWidth(tileWidth);
                            sprite->SetHeight(tileHeight);

                            sprite->Draw(position, sourceRECT, D3DXVECTOR2(), trans);
                        }
                    }
                }
            }
        }
    }

}

void Map::SetCamera(Camera* camera)
{
    this->mCamera = camera;
}

std::map<int, Sprite*> Map::getListTileSet()
{
    return mListTileset;
}

std::vector<Bee*> Map::GetListBees()
{
    return mBees;
}

QuadTree* Map::GetQuadTree()
{
    return mQuadTree;
}