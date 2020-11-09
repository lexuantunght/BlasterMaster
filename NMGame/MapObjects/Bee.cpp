#include "Bee.h"
#include "../GameGlobal.h"

Bee::Bee(D3DXVECTOR3 position)
{
    init(position);
}

Bee::~Bee()
{
}

bool Bee::init(D3DXVECTOR3 position)
{
    mAnimation = new Animation(FileName(), TotalFrame(), Row(), Column(), SecondPerFrame());

    SetPosition(position);

    Entity::SetWidth(mAnimation->GetWidth());
    Entity::SetHeight(mAnimation->GetHeight());

    return true;
}

void Bee::OnSetPosition(D3DXVECTOR3 pos)
{
    mAnimation->SetPosition(pos);
}

void Bee::Update(float dt)
{
    mAnimation->Update(dt);
}

void Bee::Draw(D3DXVECTOR3 position, RECT sourceRect, D3DXVECTOR2 scale, D3DXVECTOR2 transform, float angle, D3DXVECTOR2 rotationCenter, D3DXCOLOR colorKey)
{
    mAnimation->Draw(position, sourceRect, scale, transform, angle, rotationCenter, colorKey);
}

void Bee::Draw(D3DXVECTOR2 transform)
{
    mAnimation->Draw(transform);
}

const char* Bee::FileName()
{
    return "Assets/bee.png";
}

int Bee::TotalFrame()
{
    return 9;
}

int Bee::Row()
{
    return 1;
}

int Bee::Column()
{
    return 9;
}

float Bee::SecondPerFrame()
{
    return 0.1f;
}