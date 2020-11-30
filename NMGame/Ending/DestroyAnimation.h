#pragma once
#include "../Animation.h"
class DestroyAnimation : public Animation
{
public:
	DestroyAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL) : Animation(filePath, totalFrame, rows, columns, timePerFrame, colorKey)
	{
		timeLoad = 0;
	}
	~DestroyAnimation();
	void Reset();
	void Update(float dt);
private:
	float timeLoad;
};

