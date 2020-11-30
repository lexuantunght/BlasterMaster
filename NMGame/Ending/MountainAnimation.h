#pragma once
#include "../Animation.h"
class MountainAnimation : public Animation
{
public:
	MountainAnimation(const char* filePath, int totalFrame, int rows, int columns, float timePerFrame = 0.1f, D3DCOLOR colorKey = NULL) : Animation(filePath, totalFrame, rows, columns, timePerFrame, colorKey)
	{
		timeLoad = 0;
	}
	~MountainAnimation();
	void Reset();
	void Update(float dt);
private:
	float timeLoad;
};

