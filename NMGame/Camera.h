#pragma once
#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
private:
	int mWidth;
	int mHeight;
	D3DXVECTOR3 mPosition;
public:
    Camera(int width, int height);

    //center of camera
    void SetPosition(float x, float y);
    void SetPosition(D3DXVECTOR3 pos);

    int GetWidth();
    int GetHeight();

    D3DXVECTOR3 GetPosition();
    RECT GetBound();

    ~Camera();
};

