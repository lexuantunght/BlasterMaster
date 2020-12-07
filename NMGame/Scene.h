#pragma once
#include <d3dx9.h>
#include <d3d9.h>

#include "GameGlobal.h"

class Scene
{
public:
    virtual void Update(float dt);
    virtual void LoadContent();
    virtual void Draw();

    virtual void OnKeyDown(int keyCode);
    virtual void OnKeyUp(int keyCode);
    virtual void OnMouseDown(float x, float y);

    D3DCOLOR GetBackcolor();
    void SaveData(int missle, int thunder, int rocket, int sel, int gun);
    int* LoadData();

    virtual ~Scene();

protected:
    Scene();

    D3DCOLOR                mBackColor;

    bool isReplace;
    float timeWaitAfterDead = 0;
    D3DXVECTOR3 lastPosition;
};
